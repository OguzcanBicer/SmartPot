#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class SettingsManager {
public:
    void load(const std::string& filename = "settings.txt") {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "[Settings] Failed to open " << filename << "\n";
            return;
        }

        settings.clear();
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string key, value;
            if (std::getline(ss, key, '=') && std::getline(ss, value)) {
                settings[key] = value;
            }
        }

        std::cout << "[Settings] Loaded " << settings.size() << " values from " << filename << "\n";
    }

    int getInt(const std::string& key, int defaultVal = 0) const {
        if (settings.count(key)) return std::stoi(settings.at(key));
        return defaultVal;
    }

    std::string getString(const std::string& key, const std::string& defaultVal = "") const {
        if (settings.count(key)) return settings.at(key);
        return defaultVal;
    }

private:
    std::unordered_map<std::string, std::string> settings;
};

#endif
