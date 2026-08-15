#include "login.h"

#include <fstream>
#include <sstream>

const char* LoginService::kUserStorePath = "users.dat";

LoginService::LoginService() : session_{false, "", 0}, failedAttempts_(0) {
    loadUserStore();
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
    return true;
}

void LoginService::logout() {
    session_ = Session{false, "", 0};
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

const Session& LoginService::session() const {
    return session_;
}

std::size_t LoginService::accountCount() const {
    return accounts_.size();
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

const UserAccount* LoginService::findAccount(const std::string& username) const {
    for (const UserAccount& account : accounts_) {
        if (account.username == username) {
            return &account;
        }
    }
    return nullptr;
}

bool LoginService::hasNonEmptyFields(const Credentials& credentials) {
    return !credentials.username.empty() && !credentials.password.empty();
}
