#ifndef PROFILE_H
#define PROFILE_H

#include <string>

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
    ProfileService();
    explicit ProfileService(const Student& student);

    const ProfileRecord& current() const;
    void loadFromStudent(const Student& student);
    std::string toDisplayString() const;

    bool setDisplayName(const std::string& name);
    bool setEmail(const std::string& email);
    bool setPhone(const std::string& phone);
    bool setAddress(const std::string& address);
    bool setBio(const std::string& bio);

private:
    ProfileRecord profile_;
};

#endif
