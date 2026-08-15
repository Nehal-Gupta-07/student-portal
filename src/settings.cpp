#include "settings.h"

#include <fstream>
#include <sstream>

const char* SettingsService::kDefaultTheme = "light";
const char* SettingsService::kSettingsStorePath = "settings.dat";

SettingsService::SettingsService() {
    loadStore();
    applyDefaults("");
}

SettingsService::SettingsService(const std::string& username) {
    loadStore();
    loadForUser(username);
}

const SettingsRecord& SettingsService::current() const {
    return settings_;
}

void SettingsService::applyDefaults(const std::string& username) {
    settings_ = defaultRecord(username);
}

void SettingsService::loadForUser(const std::string& username) {
    for (const SettingsRecord& record : records_) {
        if (record.username == username) {
            settings_ = record;
            return;
        }
    }
    applyDefaults(username);
    if (!username.empty()) {
        persistCurrent();
    }
}

bool SettingsService::persistCurrent() {
    if (settings_.username.empty()) {
        return false;
    }
    upsertCurrent();
    return saveStore();
}

bool SettingsService::toggleNotifications() {
    settings_.notificationsEnabled = !settings_.notificationsEnabled;
    persistCurrent();
    return settings_.notificationsEnabled;
}

bool SettingsService::toggleEmailAlerts() {
    settings_.emailAlertsEnabled = !settings_.emailAlertsEnabled;
    persistCurrent();
    return settings_.emailAlertsEnabled;
}

bool SettingsService::setTheme(const std::string& theme) {
    if (theme != "light" && theme != "dark") {
        return false;
    }
    settings_.theme = theme;
    persistCurrent();
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

void SettingsService::loadStore() {
    records_.clear();
    std::ifstream in(kSettingsStorePath);
    if (!in) {
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        SettingsRecord record;
        if (parseRecord(line, record)) {
            records_.push_back(record);
        }
    }
}

bool SettingsService::saveStore() const {
    std::ofstream out(kSettingsStorePath);
    if (!out) {
        return false;
    }
    for (const SettingsRecord& record : records_) {
        out << record.username << ' '
            << (record.notificationsEnabled ? 1 : 0) << ' '
            << (record.emailAlertsEnabled ? 1 : 0) << ' ' << record.theme
            << '\n';
    }
    return static_cast<bool>(out);
}

void SettingsService::upsertCurrent() {
    for (SettingsRecord& record : records_) {
        if (record.username == settings_.username) {
            record = settings_;
            return;
        }
    }
    records_.push_back(settings_);
}

SettingsRecord SettingsService::defaultRecord(const std::string& username) {
    SettingsRecord record;
    record.username = username;
    record.notificationsEnabled = true;
    record.emailAlertsEnabled = true;
    record.theme = kDefaultTheme;
    return record;
}

bool SettingsService::parseRecord(const std::string& line, SettingsRecord& record) {
    std::istringstream parser(line);
    int notifications = 0;
    int emailAlerts = 0;
    if (!(parser >> record.username >> notifications >> emailAlerts >>
          record.theme)) {
        return false;
    }
    if (record.username.empty() ||
        (record.theme != "light" && record.theme != "dark")) {
        return false;
    }
    record.notificationsEnabled = notifications != 0;
    record.emailAlertsEnabled = emailAlerts != 0;
    return true;
}
