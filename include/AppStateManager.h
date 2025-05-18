#ifndef APPSTATEMANAGER_H
#define APPSTATEMANAGER_H

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include "SensorController.h"
#include "PlantProfileManager.h"

class AppStateManager {
public:
    static void save(const std::string& filename, const PlantProfile& profile, const SensorController& sensorController) {
        std::ofstream out(filename);
        if (!out.is_open()) {
            std::cerr << "Failed to write to " << filename << "\n";
            return;
        }

        out << "selectedProfile=" << profile.getName() << "\n";
        const SensorData& data = sensorController.getSensorData();
        out << "soilMoisture=" << data.getSoilMoisture() << "\n";
        out << "temperature=" << data.getTemperature() << "\n";
        out << "humidity=" << data.getHumidity() << "\n";
        out << "light=" << data.getLight() << "\n";
    }

    static void load(const std::string& filename, PlantProfileManager& profileManager, SensorController& sensorController) {
        std::ifstream in(filename);
        if (!in.is_open()) {
            std::cerr << "No previous state found.\n";
            return;
        }

        std::unordered_map<std::string, std::string> kv;
        std::string line;
        while (std::getline(in, line)) {
            std::stringstream ss(line);
            std::string key, value;
            if (std::getline(ss, key, '=') && std::getline(ss, value)) {
                kv[key] = value;
            }
        }

        // Profile seçimi
        if (kv.count("selectedProfile")) {
            std::string name = kv["selectedProfile"];
            profileManager.selectProfileByName(name);
        }

        // Sensör verilerini doğrudan set etmek gerekiyorsa friend erişimi ile:
        if (kv.count("soilMoisture") && kv.count("temperature") &&
            kv.count("humidity") && kv.count("light")) {

            sensorController.loadSensorState(
                std::stof(kv["soilMoisture"]),
                std::stof(kv["temperature"]),
                std::stof(kv["humidity"]),
                std::stof(kv["light"])
            );
        }
    }
};

#endif
