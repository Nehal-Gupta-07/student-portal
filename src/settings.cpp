#include "settings.h"

#include <sstream>

const char* SettingsService::kDefaultTheme = "light";

SettingsService::SettingsService() {
    applyDefaults("");
}

SettingsService::SettingsService(const std::string& username) {
    applyDefaults(username);
}

const SettingsRecord& SettingsService::current() const {
    return settings_;
}

void SettingsService::applyDefaults(const std::string& username) {
    settings_ = defaultRecord(username);
}

bool SettingsService::toggleNotifications() {
    settings_.notificationsEnabled = !settings_.notificationsEnabled;
    return settings_.notificationsEnabled;
}

bool SettingsService::toggleEmailAlerts() {
    settings_.emailAlertsEnabled = !settings_.emailAlertsEnabled;
    return settings_.emailAlertsEnabled;
}

bool SettingsService::setTheme(const std::string& theme) {
    if (theme != "light" && theme != "dark") {
        return false;
    }
    settings_.theme = theme;
    return true;
}

std::string SettingsService::toDisplayString() const {
    std::ostringstream out;
    out << "Username: " << (settings_.username.empty() ? "(not signed in)"
                                                       : settings_.username)
        << "\n"
        << "Notifications: "
        << (settings_.notificationsEnabled ? "on" : "off") << "\n"
        << "Email alerts: "
        << (settings_.emailAlertsEnabled ? "on" : "off") << "\n"
        << "Theme: " << settings_.theme << "\n";
    return out.str();
}

SettingsRecord SettingsService::defaultRecord(const std::string& username) {
    SettingsRecord record;
    record.username = username;
    record.notificationsEnabled = true;
    record.emailAlertsEnabled = true;
    record.theme = kDefaultTheme;
    return record;
}
