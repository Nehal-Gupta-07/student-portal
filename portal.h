#ifndef PORTAL_H
#define PORTAL_H

#include "student.h"

class Portal {
public:
    Portal();

    void run();
    const Student& currentStudent() const;

private:
    Student student_;

    void printWelcome() const;
    void printMenu() const;
    int readMenuChoice() const;
    void viewStudent() const;
    void updateName();
    void updateEmail();
    void updatePhone();
    void updateDepartment();
    void updateYear();
    void checkValidity() const;

    static void discardRestOfLine();
    static std::string readLine(const std::string& prompt);
};

#endif
