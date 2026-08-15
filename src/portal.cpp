#include "portal.h"

#include <iostream>
#include <limits>
#include <string>

Portal::Portal()
    : student_(1001, "Nehal Kumar", "nehal.kumar@university.edu", "9876543210",
               "Computer Science", 2) {}

void Portal::run() {
    printWelcome();

    bool running = true;
    while (running) {
        printMenu();
        switch (readMenuChoice()) {
            case 1:
                viewStudent();
                break;
            case 2:
                updateName();
                break;
            case 3:
                updateEmail();
                break;
            case 4:
                updatePhone();
                break;
            case 5:
                updateDepartment();
                break;
            case 6:
                updateYear();
                break;
            case 7:
                checkValidity();
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
              << "Loaded sample record for " << student_.getName() << ".\n";
}

void Portal::printMenu() const {
    std::cout << "\n===== Student Portal =====\n"
              << "1. View student record\n"
              << "2. Update name\n"
              << "3. Update email\n"
              << "4. Update phone\n"
              << "5. Update department\n"
              << "6. Update year\n"
              << "7. Check record validity\n"
              << "0. Exit\n";
}

int Portal::readMenuChoice() const {
    std::cout << "Enter choice: ";
    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        discardRestOfLine();
        return -1;
    }
    discardRestOfLine();
    return choice;
}

void Portal::viewStudent() const {
    std::cout << "\n--- Student Record ---\n"
              << student_.toDisplayString() << "\n";
}

void Portal::updateName() {
    if (!student_.setName(readLine("New name: "))) {
        std::cout << "Name cannot be empty.\n";
    } else {
        std::cout << "Name updated.\n";
    }
}

void Portal::updateEmail() {
    if (!student_.setEmail(readLine("New email: "))) {
        std::cout << "Email must look like name@domain.tld\n";
    } else {
        std::cout << "Email updated.\n";
    }
}

void Portal::updatePhone() {
    if (!student_.setPhone(readLine("New phone: "))) {
        std::cout << "Phone must have at least 10 digits.\n";
    } else {
        std::cout << "Phone updated.\n";
    }
}

void Portal::updateDepartment() {
    if (!student_.setDepartment(readLine("New department: "))) {
        std::cout << "Department cannot be empty.\n";
    } else {
        std::cout << "Department updated.\n";
    }
}

void Portal::updateYear() {
    std::cout << "New year (1-5): ";
    int year = 0;
    if (!(std::cin >> year)) {
        std::cin.clear();
        discardRestOfLine();
        std::cout << "Year must be a number.\n";
        return;
    }
    discardRestOfLine();
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

void Portal::discardRestOfLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string Portal::readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}
