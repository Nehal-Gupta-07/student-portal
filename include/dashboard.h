#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <vector>

struct Course {
    std::string code;
    std::string title;
    int credits;
};

struct Enrollment {
    std::string courseCode;
    std::string letterGrade;
};

struct Announcement {
    std::string title;
    std::string body;
    std::string postedOn;
};

class DashboardService {
public:
    DashboardService();

    const std::vector<Course>& courses() const;
    const std::vector<Enrollment>& enrollments() const;
    const std::vector<Announcement>& announcements() const;
    const Course* findCourse(const std::string& code) const;

private:
    std::vector<Course> courses_;
    std::vector<Enrollment> enrollments_;
    std::vector<Announcement> announcements_;

    void seedSampleData();
};

#endif
