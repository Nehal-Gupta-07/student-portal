#include "profile.h"

#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>

const char* ProfileService::kProfileStorePath = "profiles.dat";

namespace {

std::vector<std::string> splitFields(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    std::istringstream in(line);
    while (std::getline(in, field, '|')) {
        fields.push_back(field);
    }
    return fields;
}

}  // namespace

ProfileService::ProfileService() : profile_{0, "", "", "", "", ""} {
    loadStore();
}

ProfileService::ProfileService(const Student& student)
    : profile_{0, "", "", "", "", ""} {
    loadStore();
    if (!selectByStudentId(student.getId())) {
        loadFromStudent(student);
    }
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

void ProfileService::ensureProfile(int studentId, const Student& fallback) {
    if (selectByStudentId(studentId)) {
        return;
    }
    loadFromStudent(fallback);
    profile_.studentId = studentId;
    persistCurrent();
}

bool ProfileService::selectByStudentId(int studentId) {
    for (const ProfileRecord& record : records_) {
        if (record.studentId == studentId) {
            profile_ = record;
            return true;
        }
    }
    return false;
}

bool ProfileService::persistCurrent() {
    upsertCurrent();
    return saveStore();
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
    if (!isValidDisplayName(name)) {
        return false;
    }
    profile_.displayName = name;
    persistCurrent();
    return true;
}

bool ProfileService::setEmail(const std::string& email) {
    if (!isValidEmail(email)) {
        return false;
    }
    profile_.email = email;
    persistCurrent();
    return true;
}

bool ProfileService::setPhone(const std::string& phone) {
    if (!isValidPhone(phone)) {
        return false;
    }
    profile_.phone = phone;
    persistCurrent();
    return true;
}

bool ProfileService::setAddress(const std::string& address) {
    if (!isValidAddress(address)) {
        return false;
    }
    profile_.address = address;
    persistCurrent();
    return true;
}

bool ProfileService::setBio(const std::string& bio) {
    if (!isValidBio(bio)) {
        return false;
    }
    profile_.bio = bio;
    persistCurrent();
    return true;
}

bool ProfileService::isValidDisplayName(const std::string& name) {
    if (name.size() < 2) {
        return false;
    }
    for (char ch : name) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            return true;
        }
    }
    return false;
}

bool ProfileService::isValidEmail(const std::string& email) {
    return Student::isValidEmail(email);
}

bool ProfileService::isValidPhone(const std::string& phone) {
    return Student::isValidPhone(phone);
}

bool ProfileService::isValidAddress(const std::string& address) {
    return address.size() >= 5;
}

bool ProfileService::isValidBio(const std::string& bio) {
    return bio.size() >= 10 && bio.size() <= 280;
}

void ProfileService::loadStore() {
    records_.clear();
    std::ifstream in(kProfileStorePath);
    if (!in) {
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        ProfileRecord record;
        if (parseRecord(line, record)) {
            records_.push_back(record);
        }
    }
}

bool ProfileService::saveStore() const {
    std::ofstream out(kProfileStorePath);
    if (!out) {
        return false;
    }
    for (const ProfileRecord& record : records_) {
        out << record.studentId << '|' << sanitize(record.displayName) << '|'
            << sanitize(record.email) << '|' << sanitize(record.phone) << '|'
            << sanitize(record.address) << '|' << sanitize(record.bio) << '\n';
    }
    return static_cast<bool>(out);
}

void ProfileService::upsertCurrent() {
    for (ProfileRecord& record : records_) {
        if (record.studentId == profile_.studentId) {
            record = profile_;
            return;
        }
    }
    records_.push_back(profile_);
}

std::string ProfileService::sanitize(const std::string& value) {
    std::string cleaned = value;
    for (char& ch : cleaned) {
        if (ch == '|') {
            ch = '/';
        }
    }
    return cleaned;
}

bool ProfileService::parseRecord(const std::string& line, ProfileRecord& record) {
    const std::vector<std::string> fields = splitFields(line);
    if (fields.size() != 6) {
        return false;
    }
    try {
        record.studentId = std::stoi(fields[0]);
    } catch (...) {
        return false;
    }
    record.displayName = fields[1];
    record.email = fields[2];
    record.phone = fields[3];
    record.address = fields[4];
    record.bio = fields[5];
    return true;
}
