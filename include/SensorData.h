#ifndef SENSORDATA_H
#define SENSORDATA_H

#include "Utils.h"

class SensorData {
    friend class AppStateManager;
    friend class SensorController;
    friend class SensorSimulator;

public:
    float getSoilMoisture() const { return soilMoisture; }
    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }
    float getLight() const { return light; }

private:
    SensorData() = default;
    SensorData(float soil, float temp, float hum, float light) {
        setSoilMoisture(soil);
        setTemperature(temp);
        setHumidity(hum);
        setLight(light);
    }

    void setSoilMoisture(float value) { soilMoisture = clamp(value, 0.0f, 100.0f); }
    void setTemperature(float value) { temperature = clamp(value, -20.0f, 100.0f); }
    void setHumidity(float value) { humidity = clamp(value, 0.0f, 100.0f); }
    void setLight(float value) { light = clamp(value, 0.0f, 1000.0f); }

    float soilMoisture = 0.0f;
    float temperature = 0.0f;
    float humidity = 0.0f;
    float light = 0.0f;
};


#endif