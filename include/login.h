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

enum class PasswordChangeStatus {
    Success,
    NotAuthenticated,
    CurrentPasswordIncorrect,
    NewPasswordTooShort,
    NewPasswordSameAsOld,
    SaveFailed
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
    int remainingAttempts() const;
    const Session& session() const;
    std::size_t accountCount() const;
    PasswordChangeStatus changePassword(const std::string& currentPassword,
                                        const std::string& newPassword);
    static bool isValidNewPassword(const std::string& password);

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
    UserAccount* findAccount(const std::string& username);
    static bool hasNonEmptyFields(const Credentials& credentials);
};

#endif
