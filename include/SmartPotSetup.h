#ifndef SMARTPOTSETUP_H
#define SMARTPOTSETUP_H

#include "SensorController.h"
#include "PlantProfileManager.h"
#include "AppStateManager.h"
#include "SettingsManager.h"

class SmartPotSetup {
public:
    static void setup(SensorController& sensorController, DeviceController& deviceController, PlantProfileManager& profileManager) {
        profileManager.loadProfilesFromCSV("plants.csv");
        AppStateManager::load("save_state.txt", profileManager, sensorController);
        SettingsManager settings;
        
        settings.load("settings.txt");
        deviceController.pumpDurationSec = settings.getInt("pumpDuration", 10);
        deviceController.fanDurationSec = settings.getInt("fanDuration", 30);
        deviceController.heaterDurationSec = settings.getInt("heaterDuration", 30);
    }
};

#endif
