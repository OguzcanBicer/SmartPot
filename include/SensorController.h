#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include "SensorData.h"
#include "SensorSimulator.h"
#include "DeviceController.h"

class SensorController {
    friend class AppStateManager;

public:
    void begin(bool useSimulation = true) {
        simulate = useSimulation;
    }

    void readAllSensors(const DeviceController& deviceController, float dt = 1.0f) {
        if (simulate) {
            simulator.update(sensorData);
            simulator.applyDeviceEffects(sensorData, deviceController.getDeviceState(), dt);
        }
        // Gerçek sensörlerle çalışılacaksa buraya eklenecek
    }

    const SensorData getSensorData() const {
        return sensorData;
    }

private:
    void loadSensorState(float moisture, float temp, float hum, float light) {
        sensorData.setSoilMoisture(moisture);
        sensorData.setTemperature(temp);
        sensorData.setHumidity(hum);
        sensorData.setLight(light);
    }


    bool simulate = true;
    SensorSimulator simulator;
    SensorData sensorData;
};

#endif
