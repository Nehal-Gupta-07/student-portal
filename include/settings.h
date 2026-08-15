#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <vector>

struct SettingsRecord {
    std::string username;
    bool notificationsEnabled;
    bool emailAlertsEnabled;
    std::string theme;
};

class SettingsService {
public:
    static const char* kDefaultTheme;
    static const char* kSettingsStorePath;

    SettingsService();
    explicit SettingsService(const std::string& username);

    const SettingsRecord& current() const;
    void applyDefaults(const std::string& username);
    void loadForUser(const std::string& username);
    bool persistCurrent();
    bool toggleNotifications();
    bool toggleEmailAlerts();
    bool setTheme(const std::string& theme);
    std::string toDisplayString() const;

private:
    SettingsRecord settings_;
    std::vector<SettingsRecord> records_;

    void loadStore();
    bool saveStore() const;
    void upsertCurrent();
    static SettingsRecord defaultRecord(const std::string& username);
    static bool parseRecord(const std::string& line, SettingsRecord& record);
};

#endif
