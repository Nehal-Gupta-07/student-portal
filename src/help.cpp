#include "help.h"
#include "version.h"

#include <sstream>

std::string HelpService::formatAbout() const {
    std::ostringstream out;
    out << "Student Portal " << kPortalVersion << "\n"
        << "A command-line academic account manager with login, profile, "
           "dashboard, and settings.\n";
    return out.str();
}

std::string HelpService::formatCommandList() const {
    std::ostringstream out;
    out << "Main menu\n"
        << "1  Sign in\n"
        << "2  Sign out\n"
        << "3  View profile\n"
        << "4  Edit profile\n"
        << "5  View student record\n"
        << "6-11  Edit academic record fields and check validity\n"
        << "12 Dashboard (courses, GPA, announcements)\n"
        << "13 Settings (notifications, theme, password)\n"
        << "14 Help\n"
        << "0  Exit\n"
        << "Sign in before using profile, dashboard, or settings.\n"
        << "Sample accounts: nehal/portal123 and student/student123\n";
    return out.str();
}
