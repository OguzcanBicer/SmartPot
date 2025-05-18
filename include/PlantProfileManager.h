#ifndef PLANTPROFILEMANAGER_H
#define PLANTPROFILEMANAGER_H

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "PlantProfile.h"

class PlantProfileManager {
public:
    PlantProfileManager() = default;

    void loadProfilesFromCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open plant profile CSV file: " << filename << "\n";
            return;
        }

        profiles.clear();
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue; // yorum satırı veya boş geç

            std::stringstream ss(line);
            std::string item, name;

            std::getline(ss, name, ',');                       // name
            std::getline(ss, item, ','); float minSoil = std::stof(item);
            std::getline(ss, item, ','); float maxSoil = std::stof(item);
            std::getline(ss, item, ','); float minTemp = std::stof(item);
            std::getline(ss, item, ','); float maxTemp = std::stof(item);
            std::getline(ss, item, ','); float minHum  = std::stof(item);
            std::getline(ss, item, ','); float maxHum  = std::stof(item);
            std::getline(ss, item, ','); float minLight = std::stof(item);
            std::getline(ss, item, ','); float lightHours = std::stof(item);

            PlantProfile profile(name, minSoil, maxSoil, minTemp, maxTemp, minHum, maxHum, minLight, lightHours);
            profiles.push_back(profile);
        }

        if (!profiles.empty()) {
            selectedProfile = profiles[0];
            std::cout << "[PlantProfileManager] Loaded " << profiles.size() << " profiles.\n";
        } else {
            std::cerr << "[PlantProfileManager] No profiles loaded from " << filename << "\n";
        }
    }


    void listProfiles() const {
        std::cout << "\nAvailable Plant Profiles:\n";
        for (size_t i = 0; i < profiles.size(); ++i) {
            std::cout << i + 1 << ". " << profiles[i].name << "\n";
        }
    }

    void selectProfile(int index) {
        if (index >= 1 && index <= profiles.size()) {
            selectedProfile = profiles[index - 1];
            std::cout << "Selected profile: " << selectedProfile.name << "\n";
        } else {
            std::cout << "Invalid selection.\n";
        }
    }

    void selectProfileByName(const std::string& name) {
        for (size_t i = 0; i < profiles.size(); ++i) {
            if (profiles[i].getName() == name) {
                selectProfile(i + 1); // zaten 1-based çalışıyorsun
                return;
            }
        }
        std::cerr << "Profile with name '" << name << "' not found.\n";
    }


    void showSelectedProfile() const {
        selectedProfile.print();
    }

    const PlantProfile& getSelectedProfile() const {
        return selectedProfile;
    }

private:

    std::vector<PlantProfile> profiles;
    PlantProfile selectedProfile;
};
#endif
