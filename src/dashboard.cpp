#include "dashboard.h"

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
