#ifndef PORTAL_H
#define PORTAL_H

#include "login.h"
#include "student.h"

class Portal {
public:
    Portal();

    void run();
    const Student& currentStudent() const;

private:
    Student student_;
    LoginService login_;

    void printWelcome() const;
    void printMenu() const;
    int readMenuChoice() const;
    bool requireLogin() const;
    void promptLogin();
    void promptLogout();
    void viewStudent() const;
    void updateName();
    void updateEmail();
    void updatePhone();
    void updateDepartment();
    void updateYear();
    void checkValidity() const;
};

#endif
