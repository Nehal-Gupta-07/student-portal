#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <vector>

#include "student.h"

struct ProfileRecord {
    int studentId;
    std::string displayName;
    std::string email;
    std::string phone;
    std::string address;
    std::string bio;
};

class ProfileService {
public:
    static const char* kProfileStorePath;

    ProfileService();
    explicit ProfileService(const Student& student);

    const ProfileRecord& current() const;
    void loadFromStudent(const Student& student);
    void ensureProfile(int studentId, const Student& fallback);
    bool selectByStudentId(int studentId);
    bool persistCurrent();
    std::string toDisplayString() const;

    bool setDisplayName(const std::string& name);
    bool setEmail(const std::string& email);
    bool setPhone(const std::string& phone);
    bool setAddress(const std::string& address);
    bool setBio(const std::string& bio);

    static bool isValidDisplayName(const std::string& name);
    static bool isValidEmail(const std::string& email);
    static bool isValidPhone(const std::string& phone);
    static bool isValidAddress(const std::string& address);
    static bool isValidBio(const std::string& bio);

private:
    ProfileRecord profile_;
    std::vector<ProfileRecord> records_;

    void loadStore();
    bool saveStore() const;
    void upsertCurrent();
    static std::string sanitize(const std::string& value);
    static bool parseRecord(const std::string& line, ProfileRecord& record);
};

#endif
