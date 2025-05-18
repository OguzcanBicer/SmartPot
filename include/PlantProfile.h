#ifndef PLANTPROFILE_H
#define PLANTPROFILE_H

#include <string>
#include <iostream>
#include "Utils.h"

struct PlantProfile {
    friend class PlantProfileManager;

    const std::string& getName() const { return name; }
    float getMinSoilMoisture() const { return minSoilMoisture; }
    float getMaxSoilMoisture() const { return maxSoilMoisture; }
    float getMinTemperature() const { return minTemperature; }
    float getMaxTemperature() const { return maxTemperature; }
    float getMinHumidity() const { return minHumidity; }
    float getMaxHumidity() const { return maxHumidity; }
    float getMinLight() const { return minLight; }
    float getRequiredLightHours() const { return requiredLightHours; }


    void print() const {
        std::cout << "\n--- Plant Profile: " << name << " ---\n";
        std::cout << "Soil Moisture    : " << minSoilMoisture << " - " << maxSoilMoisture << " %\n";
        std::cout << "Temperature      : " << minTemperature << " - " << maxTemperature << " °C\n";
        std::cout << "Humidity         : " << minHumidity << " - " << maxHumidity << " %\n";
        std::cout << "Min Light        : " << minLight << " lux\n";
        std::cout << "Required Light   : " << requiredLightHours << " hrs/day\n";
    }


private:
    PlantProfile() = default;
    PlantProfile(std::string name,
                 float minSoil, float maxSoil,
                 float minTemp, float maxTemp,
                 float minHum, float maxHum,
                 float minLight, float lightHours)
        : name(std::move(name)),
          minSoilMoisture(minSoil), maxSoilMoisture(maxSoil),
          minTemperature(minTemp), maxTemperature(maxTemp),
          minHumidity(minHum), maxHumidity(maxHum),
          minLight(minLight), requiredLightHours(lightHours) {}

    void setMinSoilMoisture(float value) {
        minSoilMoisture = clamp(value, 0.0f, 100.0f);
    }

    void setTemperatureRange(float minTemp, float maxTemp) {
        minTemperature = std::min(minTemp, maxTemp);
        maxTemperature = std::max(minTemp, maxTemp);
    }

    void setMinLight(float value) {
        minLight = std::max(0.0f, value);
    }

    std::string name = "Unnamed";

    float minSoilMoisture = 0.0f;
    float maxSoilMoisture = 100.0f;

    float minTemperature = 0.0f;
    float maxTemperature = 40.0f;

    float minHumidity = 0.0f;
    float maxHumidity = 100.0f;

    float minLight = 300.0f;        // lux
    float requiredLightHours = 12.0f;

};
#endif
