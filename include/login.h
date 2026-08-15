#ifndef LOGIN_H
#define LOGIN_H

#include <string>

struct Session {
    bool authenticated;
    std::string username;
    int studentId;
};

struct Credentials {
    std::string username;
    std::string password;
};

class LoginService {
public:
    static const int kMaxFailedAttempts = 3;

    LoginService();

    bool login(const Credentials& credentials);
    void logout();

    bool isAuthenticated() const;
    bool isLocked() const;
    int failedAttempts() const;
    const Session& session() const;

private:
    Session session_;
    int failedAttempts_;

    static bool hasNonEmptyFields(const Credentials& credentials);
};

#endif
