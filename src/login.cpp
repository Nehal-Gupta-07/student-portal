#include "login.h"

LoginService::LoginService() : session_{false, "", 0}, failedAttempts_(0) {}

bool LoginService::login(const Credentials& credentials) {
    if (isLocked()) {
        return false;
    }
    if (!hasNonEmptyFields(credentials)) {
        ++failedAttempts_;
        session_ = Session{false, "", 0};
        return false;
    }

    // Credential store lookup is added in the next login commit.
    session_.authenticated = true;
    session_.username = credentials.username;
    session_.studentId = 1001;
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

bool LoginService::hasNonEmptyFields(const Credentials& credentials) {
    return !credentials.username.empty() && !credentials.password.empty();
}
