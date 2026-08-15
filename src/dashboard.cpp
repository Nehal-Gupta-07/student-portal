#include "dashboard.h"

#include <iomanip>
#include <sstream>

DashboardService::DashboardService() {
    seedSampleData();
}

const std::vector<Course>& DashboardService::courses() const {
    return courses_;
}

const std::vector<Enrollment>& DashboardService::enrollments() const {
    return enrollments_;
}

const std::vector<Announcement>& DashboardService::announcements() const {
    return announcements_;
}

const Course* DashboardService::findCourse(const std::string& code) const {
    for (const Course& course : courses_) {
        if (course.code == code) {
            return &course;
        }
    }
    return nullptr;
}

std::string DashboardService::formatEnrollmentList() const {
    std::ostringstream out;
    out << "Code    Credits  Grade  Title\n"
        << "------  -------  -----  -----\n";
    if (enrollments_.empty()) {
        out << "(no enrolled courses)\n";
        return out.str();
    }
    for (const Enrollment& enrollment : enrollments_) {
        const Course* course = findCourse(enrollment.courseCode);
        const std::string title = course != nullptr ? course->title : "Unknown course";
        const int credits = course != nullptr ? course->credits : 0;
        out << enrollment.courseCode;
        if (enrollment.courseCode.size() < 8) {
            out << std::string(8 - enrollment.courseCode.size(), ' ');
        }
        out << credits << "        " << enrollment.letterGrade;
        if (enrollment.letterGrade.size() < 7) {
            out << std::string(7 - enrollment.letterGrade.size(), ' ');
        }
        out << title << "\n";
    }
    out << "Total credits: " << enrolledCreditTotal() << "\n";
    return out.str();
}

int DashboardService::enrolledCreditTotal() const {
    int total = 0;
    for (const Enrollment& enrollment : enrollments_) {
        const Course* course = findCourse(enrollment.courseCode);
        if (course != nullptr) {
            total += course->credits;
        }
    }
    return total;
}

double DashboardService::letterToPoints(const std::string& letterGrade) {
    if (letterGrade == "A" || letterGrade == "A+") {
        return 10.0;
    }
    if (letterGrade == "A-") {
        return 9.0;
    }
    if (letterGrade == "B+") {
        return 8.0;
    }
    if (letterGrade == "B") {
        return 7.0;
    }
    if (letterGrade == "B-") {
        return 6.0;
    }
    if (letterGrade == "C+") {
        return 5.0;
    }
    if (letterGrade == "C") {
        return 4.0;
    }
    if (letterGrade == "D") {
        return 2.0;
    }
    return 0.0;
}

double DashboardService::computeGpa() const {
    double weighted = 0.0;
    int credits = 0;
    for (const Enrollment& enrollment : enrollments_) {
        const Course* course = findCourse(enrollment.courseCode);
        if (course == nullptr || course->credits <= 0) {
            continue;
        }
        weighted += letterToPoints(enrollment.letterGrade) * course->credits;
        credits += course->credits;
    }
    if (credits == 0) {
        return 0.0;
    }
    return weighted / credits;
}

std::string DashboardService::formatGpaSummary() const {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2);
    out << "GPA summary (10-point scale)\n"
        << "Courses counted: " << enrollments_.size() << "\n"
        << "Credits counted: " << enrolledCreditTotal() << "\n"
        << "GPA: " << computeGpa() << "\n";
    return out.str();
}

std::string DashboardService::formatAnnouncementFeed() const {
    std::ostringstream out;
    out << "Announcements\n"
        << "-------------\n";
    if (announcements_.empty()) {
        out << "(no announcements)\n";
        return out.str();
    }
    for (std::size_t i = announcements_.size(); i > 0; --i) {
        const Announcement& item = announcements_[i - 1];
        out << "[" << item.postedOn << "] " << item.title << "\n"
            << item.body << "\n\n";
    }
    return out.str();
}

void DashboardService::seedSampleData() {
    courses_.clear();
    courses_.push_back(Course{"CS101", "Introduction to Programming", 4});
    courses_.push_back(Course{"CS201", "Data Structures", 4});
    courses_.push_back(Course{"MA102", "Discrete Mathematics", 3});
    courses_.push_back(Course{"HS110", "Technical Communication", 2});

    enrollments_.clear();
    enrollments_.push_back(Enrollment{"CS101", "A"});
    enrollments_.push_back(Enrollment{"CS201", "B+"});
    enrollments_.push_back(Enrollment{"MA102", "A-"});
    enrollments_.push_back(Enrollment{"HS110", "B"});

    announcements_.clear();
    announcements_.push_back(Announcement{
        "Midterm schedule", "CS201 midterm is on 12 September in Hall 2.",
        "2026-08-10"});
    announcements_.push_back(Announcement{
        "Library hours", "The library stays open until 11 PM during exam week.",
        "2026-08-12"});
    announcements_.push_back(Announcement{
        "Club fair", "Student clubs will set up booths in the quad on Friday.",
        "2026-08-14"});
}
