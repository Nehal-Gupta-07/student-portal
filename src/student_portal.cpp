#include "portal.h"

#include "console_io.h"

#include <iostream>
#include <string>

Portal::Portal()
    : student_(1001, "Nehal Kumar", "nehal.kumar@university.edu", "9876543210",
               "Computer Science", 2),
      profile_(student_) {}

void Portal::run() {
    printWelcome();

    bool running = true;
    while (running) {
        printMenu();
        switch (readMenuChoice()) {
            case 1:
                promptLogin();
                break;
            case 2:
                promptLogout();
                break;
            case 3:
                if (requireLogin()) {
                    viewProfile();
                }
                break;
            case 4:
                if (requireLogin()) {
                    viewStudent();
                }
                break;
            case 5:
                if (requireLogin()) {
                    updateName();
                }
                break;
            case 6:
                if (requireLogin()) {
                    updateEmail();
                }
                break;
            case 7:
                if (requireLogin()) {
                    updatePhone();
                }
                break;
            case 8:
                if (requireLogin()) {
                    updateDepartment();
                }
                break;
            case 9:
                if (requireLogin()) {
                    updateYear();
                }
                break;
            case 10:
                if (requireLogin()) {
                    checkValidity();
                }
                break;
            case 0:
                running = false;
                std::cout << "Goodbye.\n";
                break;
            default:
                std::cout << "Unknown choice. Pick a menu number.\n";
                break;
        }
    }
}

const Student& Portal::currentStudent() const {
    return student_;
}

void Portal::printWelcome() const {
    std::cout << "Welcome to Student Portal\n"
              << "Loaded " << login_.accountCount()
              << " account(s) from the local user store.\n";
    if (login_.isAuthenticated()) {
        std::cout << "Restored session for " << login_.session().username << ".\n";
    } else {
        std::cout << "Sign in before viewing or editing a student record.\n";
    }
}

void Portal::printMenu() const {
    std::cout << "\n===== Student Portal =====\n";
    if (login_.isAuthenticated()) {
        std::cout << "Signed in as " << login_.session().username << "\n";
    } else {
        std::cout << "Not signed in\n";
    }
    std::cout << "1. Sign in\n"
              << "2. Sign out\n"
              << "3. View profile\n"
              << "4. View student record\n"
              << "5. Update name\n"
              << "6. Update email\n"
              << "7. Update phone\n"
              << "8. Update department\n"
              << "9. Update year\n"
              << "10. Check record validity\n"
              << "0. Exit\n";
}

int Portal::readMenuChoice() const {
    bool ok = false;
    const int choice = console::readInt("Enter choice: ", ok);
    if (!ok) {
        return -1;
    }
    return choice;
}

bool Portal::requireLogin() const {
    if (login_.isAuthenticated()) {
        return true;
    }
    std::cout << "Please sign in first.\n";
    return false;
}

void Portal::promptLogin() {
    if (login_.isAuthenticated()) {
        std::cout << "Already signed in as " << login_.session().username << ".\n";
        return;
    }
    if (login_.isLocked()) {
        std::cout << "Sign-in is locked after " << LoginService::kMaxFailedAttempts
                  << " failed attempts. Close the program and start it again to retry.\n";
        return;
    }

    Credentials credentials;
    credentials.username = console::readLine("Username: ");
    credentials.password = console::readLine("Password: ");

    if (login_.login(credentials)) {
        std::cout << "Signed in as " << login_.session().username << ".\n";
        return;
    }

    if (login_.isLocked()) {
        std::cout << "Too many failed attempts. Sign-in is now locked until you restart the program.\n";
        return;
    }

    std::cout << "Sign-in failed. " << login_.remainingAttempts()
              << " attempt(s) remaining.\n";
}

void Portal::promptLogout() {
    if (!login_.isAuthenticated()) {
        std::cout << "You are not signed in.\n";
        return;
    }
    login_.logout();
    std::cout << "Signed out.\n";
}

void Portal::viewProfile() const {
    std::cout << "\n--- Student Profile ---\n"
              << profile_.toDisplayString() << "\n";
}

void Portal::viewStudent() const {
    std::cout << "\n--- Student Record ---\n"
              << student_.toDisplayString() << "\n";
}

void Portal::updateName() {
    if (!student_.setName(console::readLine("New name: "))) {
        std::cout << "Name cannot be empty.\n";
    } else {
        std::cout << "Name updated.\n";
    }
}

void Portal::updateEmail() {
    if (!student_.setEmail(console::readLine("New email: "))) {
        std::cout << "Email must look like name@domain.tld\n";
    } else {
        std::cout << "Email updated.\n";
    }
}

void Portal::updatePhone() {
    if (!student_.setPhone(console::readLine("New phone: "))) {
        std::cout << "Phone must have at least 10 digits.\n";
    } else {
        std::cout << "Phone updated.\n";
    }
}

void Portal::updateDepartment() {
    if (!student_.setDepartment(console::readLine("New department: "))) {
        std::cout << "Department cannot be empty.\n";
    } else {
        std::cout << "Department updated.\n";
    }
}

void Portal::updateYear() {
    bool ok = false;
    const int year = console::readInt("New year (1-5): ", ok);
    if (!ok) {
        std::cout << "Year must be a number.\n";
        return;
    }
    if (!student_.setYear(year)) {
        std::cout << "Year must be between 1 and 5.\n";
    } else {
        std::cout << "Year updated.\n";
    }
}

void Portal::checkValidity() const {
    std::cout << (student_.isValid() ? "Record is complete and valid.\n"
                                    : "Record is missing or invalid fields.\n");
}
