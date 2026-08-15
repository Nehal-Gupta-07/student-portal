#include <iostream>
#include <limits>
#include <string>

#include "student.h"

namespace {

void discardRestOfLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

int readMenuChoice() {
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

void printMenu() {
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

void viewStudent(const Student& student) {
    std::cout << "\n--- Student Record ---\n"
              << student.toDisplayString() << "\n";
}

}  // namespace

int main() {
    Student student(1001, "Nehal Kumar", "nehal.kumar@university.edu",
                    "9876543210", "Computer Science", 2);

    std::cout << "Welcome to Student Portal\n"
              << "Loaded sample record for " << student.getName() << ".\n";

    bool running = true;
    while (running) {
        printMenu();
        switch (readMenuChoice()) {
            case 1:
                viewStudent(student);
                break;
            case 2:
                if (!student.setName(readLine("New name: "))) {
                    std::cout << "Name cannot be empty.\n";
                } else {
                    std::cout << "Name updated.\n";
                }
                break;
            case 3:
                if (!student.setEmail(readLine("New email: "))) {
                    std::cout << "Email must look like name@domain.tld\n";
                } else {
                    std::cout << "Email updated.\n";
                }
                break;
            case 4:
                if (!student.setPhone(readLine("New phone: "))) {
                    std::cout << "Phone must have at least 10 digits.\n";
                } else {
                    std::cout << "Phone updated.\n";
                }
                break;
            case 5:
                if (!student.setDepartment(readLine("New department: "))) {
                    std::cout << "Department cannot be empty.\n";
                } else {
                    std::cout << "Department updated.\n";
                }
                break;
            case 6: {
                std::cout << "New year (1-5): ";
                int year = 0;
                if (!(std::cin >> year)) {
                    std::cin.clear();
                    discardRestOfLine();
                    std::cout << "Year must be a number.\n";
                    break;
                }
                discardRestOfLine();
                if (!student.setYear(year)) {
                    std::cout << "Year must be between 1 and 5.\n";
                } else {
                    std::cout << "Year updated.\n";
                }
                break;
            }
            case 7:
                std::cout << (student.isValid()
                                  ? "Record is complete and valid.\n"
                                  : "Record is missing or invalid fields.\n");
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

    return 0;
}
