#ifndef PORTAL_H
#define PORTAL_H

#include "dashboard.h"
#include "login.h"
#include "profile.h"
#include "student.h"

class Portal {
public:
    Portal();

    void run();
    const Student& currentStudent() const;

private:
    Student student_;
    LoginService login_;
    ProfileService profile_;
    DashboardService dashboard_;

    void printWelcome() const;
    void printMenu() const;
    int readMenuChoice() const;
    bool requireLogin() const;
    void promptLogin();
    void promptLogout();
    void loadProfileForSession();
    void viewProfile() const;
    void editProfileMenu();
    void updateProfileName();
    void updateProfileEmail();
    void updateProfilePhone();
    void updateProfileAddress();
    void updateProfileBio();
    void viewStudent() const;
    void updateName();
    void updateEmail();
    void updatePhone();
    void updateDepartment();
    void updateYear();
    void checkValidity() const;
    void dashboardMenu() const;
    void viewEnrolledCourses() const;
    void viewGpaSummary() const;
    void viewAnnouncements() const;
    void viewFullDashboard() const;
};

#endif
