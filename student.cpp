#include "student.h"

#include <cctype>
#include <sstream>

Student::Student()
    : id_(0), name_(), email_(), phone_(), department_(), year_(1) {}

Student::Student(int id, const std::string& name, const std::string& email,
                 const std::string& phone, const std::string& department, int year)
    : id_(id), name_(), email_(), phone_(), department_(), year_(1) {
    setName(name);
    setEmail(email);
    setPhone(phone);
    setDepartment(department);
    setYear(year);
}

int Student::getId() const {
    return id_;
}

const std::string& Student::getName() const {
    return name_;
}

const std::string& Student::getEmail() const {
    return email_;
}

const std::string& Student::getPhone() const {
    return phone_;
}

const std::string& Student::getDepartment() const {
    return department_;
}

int Student::getYear() const {
    return year_;
}

bool Student::setName(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    name_ = name;
    return true;
}

bool Student::setEmail(const std::string& email) {
    if (!isValidEmail(email)) {
        return false;
    }
    email_ = email;
    return true;
}

bool Student::setPhone(const std::string& phone) {
    if (!isValidPhone(phone)) {
        return false;
    }
    phone_ = phone;
    return true;
}

bool Student::setDepartment(const std::string& department) {
    if (department.empty()) {
        return false;
    }
    department_ = department;
    return true;
}

bool Student::setYear(int year) {
    if (!isValidYear(year)) {
        return false;
    }
    year_ = year;
    return true;
}

bool Student::isValid() const {
    return id_ > 0 && !name_.empty() && isValidEmail(email_) &&
           isValidPhone(phone_) && !department_.empty() && isValidYear(year_);
}

std::string Student::toDisplayString() const {
    std::ostringstream out;
    out << "ID: " << id_ << "\n"
        << "Name: " << name_ << "\n"
        << "Email: " << email_ << "\n"
        << "Phone: " << phone_ << "\n"
        << "Department: " << department_ << "\n"
        << "Year: " << year_;
    return out.str();
}

bool Student::isValidEmail(const std::string& email) {
    const std::string::size_type at = email.find('@');
    if (at == std::string::npos || at == 0) {
        return false;
    }
    const std::string::size_type dot = email.find('.', at + 1);
    return dot != std::string::npos && dot > at + 1 && dot + 1 < email.size();
}

bool Student::isValidPhone(const std::string& phone) {
    if (phone.size() < 10) {
        return false;
    }
    for (char ch : phone) {
        if (!std::isdigit(static_cast<unsigned char>(ch)) && ch != '+' &&
            ch != '-' && ch != ' ') {
            return false;
        }
    }
    return true;
}

bool Student::isValidYear(int year) {
    return year >= 1 && year <= 5;
}
