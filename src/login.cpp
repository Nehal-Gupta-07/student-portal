#include "login.h"

#include <fstream>
#include <sstream>

const char* LoginService::kUserStorePath = "users.dat";
const char* LoginService::kSessionPath = "session.dat";

LoginService::LoginService() : session_{false, "", 0}, failedAttempts_(0) {
    loadUserStore();
    loadSession();
}

bool LoginService::login(const Credentials& credentials) {
    if (isLocked()) {
        return false;
    }
    if (!hasNonEmptyFields(credentials)) {
        ++failedAttempts_;
        session_ = Session{false, "", 0};
        return false;
    }

    const UserAccount* account = findAccount(credentials.username);
    if (account == nullptr || account->password != credentials.password) {
        ++failedAttempts_;
        session_ = Session{false, "", 0};
        return false;
    }

    session_.authenticated = true;
    session_.username = account->username;
    session_.studentId = account->studentId;
    failedAttempts_ = 0;
    saveSession();
    return true;
}

void LoginService::logout() {
    session_ = Session{false, "", 0};
    clearSessionFile();
}

bool LoginService::isAuthenticated() const {
    return session_.authenticated;
}

bool LoginService::isLocked() const {
    return failedAttempts_ >= kMaxFailedAttempts;
}

int LoginService::failedAttempts() const {
    return failedAttempts_;
}

int LoginService::remainingAttempts() const {
    if (failedAttempts_ >= kMaxFailedAttempts) {
        return 0;
    }
    return kMaxFailedAttempts - failedAttempts_;
}

const Session& LoginService::session() const {
    return session_;
}

std::size_t LoginService::accountCount() const {
    return accounts_.size();
}

bool LoginService::isValidNewPassword(const std::string& password) {
    return password.size() >= 8;
}

PasswordChangeStatus LoginService::changePassword(
    const std::string& currentPassword, const std::string& newPassword) {
    if (!isAuthenticated()) {
        return PasswordChangeStatus::NotAuthenticated;
    }
    UserAccount* account = findAccount(session_.username);
    if (account == nullptr || account->password != currentPassword) {
        return PasswordChangeStatus::CurrentPasswordIncorrect;
    }
    if (!isValidNewPassword(newPassword)) {
        return PasswordChangeStatus::NewPasswordTooShort;
    }
    if (newPassword == currentPassword) {
        return PasswordChangeStatus::NewPasswordSameAsOld;
    }
    account->password = newPassword;
    if (!saveUserStore()) {
        return PasswordChangeStatus::SaveFailed;
    }
    return PasswordChangeStatus::Success;
}

void LoginService::loadUserStore() {
    accounts_.clear();
    std::ifstream in(kUserStorePath);
    if (!in) {
        seedDefaultAccounts();
        saveUserStore();
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream parser(line);
        UserAccount account;
        if (parser >> account.username >> account.password >> account.studentId) {
            accounts_.push_back(account);
        }
    }

    if (accounts_.empty()) {
        seedDefaultAccounts();
        saveUserStore();
    }
}

void LoginService::seedDefaultAccounts() {
    accounts_.clear();
    accounts_.push_back(UserAccount{"nehal", "portal123", 1001});
    accounts_.push_back(UserAccount{"student", "student123", 1002});
}

bool LoginService::saveUserStore() const {
    std::ofstream out(kUserStorePath);
    if (!out) {
        return false;
    }
    for (const UserAccount& account : accounts_) {
        out << account.username << ' ' << account.password << ' '
            << account.studentId << '\n';
    }
    return static_cast<bool>(out);
}

void LoginService::loadSession() {
    session_ = Session{false, "", 0};
    std::ifstream in(kSessionPath);
    if (!in) {
        return;
    }

    std::string username;
    int studentId = 0;
    if (!(in >> username >> studentId) || username.empty()) {
        return;
    }

    const UserAccount* account = findAccount(username);
    if (account == nullptr || account->studentId != studentId) {
        clearSessionFile();
        return;
    }

    session_.authenticated = true;
    session_.username = account->username;
    session_.studentId = account->studentId;
}

bool LoginService::saveSession() const {
    if (!session_.authenticated) {
        return clearSessionFile();
    }
    std::ofstream out(kSessionPath);
    if (!out) {
        return false;
    }
    out << session_.username << ' ' << session_.studentId << '\n';
    return static_cast<bool>(out);
}

bool LoginService::clearSessionFile() const {
    std::ofstream out(kSessionPath, std::ios::trunc);
    return static_cast<bool>(out);
}

const UserAccount* LoginService::findAccount(const std::string& username) const {
    for (const UserAccount& account : accounts_) {
        if (account.username == username) {
            return &account;
        }
    }
    return nullptr;
}

UserAccount* LoginService::findAccount(const std::string& username) {
    for (UserAccount& account : accounts_) {
        if (account.username == username) {
            return &account;
        }
    }
    return nullptr;
}

bool LoginService::hasNonEmptyFields(const Credentials& credentials) {
    return !credentials.username.empty() && !credentials.password.empty();
}
