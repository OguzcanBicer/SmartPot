#ifndef SMARTPOTLOOP_H
#define SMARTPOTLOOP_H

#include "SensorController.h"
#include "DeviceController.h"
#include "PlantProfileManager.h"
#include "AutoDecisionEngine.h"
#include "MenuManager.h"

#include <chrono>

class SmartPotLoop {
public:
    SmartPotLoop() = default;
    DeviceController* deviceController;
    PlantProfileManager* profileManager;
    AutoDecisionEngine* engine;
    SensorController* sensorController;

    std::chrono::steady_clock::time_point lastUpdate;

    void begin(SensorController& s, DeviceController& d, PlantProfileManager& p, AutoDecisionEngine& e, bool simulation) {
        deviceController = &d;
        profileManager = &p;
        engine = &e;
        sensorController = &s;               
        sensorController->begin(simulation); 
        lastUpdate = std::chrono::steady_clock::now();
    }

    void loop() {
        using namespace std::chrono;
        auto now = steady_clock::now();
        float dt = duration<float>(now - lastUpdate).count();

        if (dt >= 3.0f) {
            lastUpdate = now;
            MenuManager::clearScreen();

            sensorController->readAllSensors(*deviceController, dt);
            deviceController->updateTimers();
            engine->evaluate(*sensorController, *deviceController, profileManager->getSelectedProfile());
            MenuManager::showStatus(*sensorController, profileManager->getSelectedProfile(), *deviceController);
        }
    }
};

#endif