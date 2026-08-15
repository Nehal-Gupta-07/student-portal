#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>

struct Session {
    bool authenticated;
    std::string username;
    int studentId;
};

struct Credentials {
    std::string username;
    std::string password;
};

struct UserAccount {
    std::string username;
    std::string password;
    int studentId;
};

class LoginService {
public:
    static const int kMaxFailedAttempts = 3;
    static const char* kUserStorePath;
    static const char* kSessionPath;

    LoginService();

    bool login(const Credentials& credentials);
    void logout();

    bool isAuthenticated() const;
    bool isLocked() const;
    int failedAttempts() const;
    const Session& session() const;
    std::size_t accountCount() const;

private:
    Session session_;
    int failedAttempts_;
    std::vector<UserAccount> accounts_;

    void loadUserStore();
    void seedDefaultAccounts();
    bool saveUserStore() const;
    void loadSession();
    bool saveSession() const;
    bool clearSessionFile() const;
    const UserAccount* findAccount(const std::string& username) const;
    static bool hasNonEmptyFields(const Credentials& credentials);
};

#endif
