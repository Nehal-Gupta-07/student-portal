#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

struct SettingsRecord {
    std::string username;
    bool notificationsEnabled;
    bool emailAlertsEnabled;
    std::string theme;
};

class SettingsService {
public:
    static const char* kDefaultTheme;

    SettingsService();
    explicit SettingsService(const std::string& username);

    const SettingsRecord& current() const;
    void applyDefaults(const std::string& username);
    std::string toDisplayString() const;

private:
    SettingsRecord settings_;

    static SettingsRecord defaultRecord(const std::string& username);
};

#endif
