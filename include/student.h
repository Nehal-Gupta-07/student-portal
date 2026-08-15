#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    Student();
    Student(int id, const std::string& name, const std::string& email,
            const std::string& phone, const std::string& department, int year);

    int getId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& getPhone() const;
    const std::string& getDepartment() const;
    int getYear() const;

    bool setName(const std::string& name);
    bool setEmail(const std::string& email);
    bool setPhone(const std::string& phone);
    bool setDepartment(const std::string& department);
    bool setYear(int year);

    bool isValid() const;
    std::string toDisplayString() const;

    static bool isValidEmail(const std::string& email);
    static bool isValidPhone(const std::string& phone);
    static bool isValidYear(int year);

private:
    int id_;
    std::string name_;
    std::string email_;
    std::string phone_;
    std::string department_;
    int year_;
};

#endif
