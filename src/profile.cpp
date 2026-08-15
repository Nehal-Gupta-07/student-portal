#include "profile.h"

#include <sstream>

ProfileService::ProfileService() : profile_{0, "", "", "", "", ""} {}

ProfileService::ProfileService(const Student& student) : profile_{0, "", "", "", "", ""} {
    loadFromStudent(student);
}

const ProfileRecord& ProfileService::current() const {
    return profile_;
}

void ProfileService::loadFromStudent(const Student& student) {
    profile_.studentId = student.getId();
    profile_.displayName = student.getName();
    profile_.email = student.getEmail();
    profile_.phone = student.getPhone();
    profile_.address = "Not set";
    profile_.bio = "No bio yet.";
}

std::string ProfileService::toDisplayString() const {
    std::ostringstream out;
    out << "Student ID: " << profile_.studentId << "\n"
        << "Display name: " << profile_.displayName << "\n"
        << "Email: " << profile_.email << "\n"
        << "Phone: " << profile_.phone << "\n"
        << "Address: " << profile_.address << "\n"
        << "Bio: " << profile_.bio;
    return out.str();
}

bool ProfileService::setDisplayName(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    profile_.displayName = name;
    return true;
}

bool ProfileService::setEmail(const std::string& email) {
    if (email.empty()) {
        return false;
    }
    profile_.email = email;
    return true;
}

bool ProfileService::setPhone(const std::string& phone) {
    if (phone.empty()) {
        return false;
    }
    profile_.phone = phone;
    return true;
}

bool ProfileService::setAddress(const std::string& address) {
    if (address.empty()) {
        return false;
    }
    profile_.address = address;
    return true;
}

bool ProfileService::setBio(const std::string& bio) {
    if (bio.empty()) {
        return false;
    }
    profile_.bio = bio;
    return true;
}
