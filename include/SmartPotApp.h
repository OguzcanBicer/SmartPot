#ifndef SMARTPOTAPP_H
#define SMARTPOTAPP_H

#include "SmartPotSetup.h"
#include "SmartPotLoop.h"

class SmartPotApp {
public:
    SensorController sensorController;
    DeviceController deviceController;
    PlantProfileManager profileManager;
    AutoDecisionEngine autoDecisionEngine;
    SmartPotLoop loopLogic;

    void setup(bool simulate = true) {
        SmartPotSetup::setup(sensorController, deviceController, profileManager);
        loopLogic.begin(sensorController, deviceController, profileManager, autoDecisionEngine, simulate);
    }

    void loop() {
        loopLogic.loop();
    }
};

#endif