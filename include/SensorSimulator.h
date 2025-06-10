#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include "SensorData.h"
#include "DeviceController.h"
#include "Utils.h"
#include <chrono>
#include <random>
#include <algorithm>

class SensorSimulator {
    friend class SensorController;

private:
    SensorSimulator() {
        lastUpdate = std::chrono::steady_clock::now();
    }

    void update(SensorData& sensorData) {
        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - lastUpdate).count();
        lastUpdate = now;

        drift(sensorData.soilMoisture, dirSoil, 0.1f * dt, 0, 100);
        drift(sensorData.temperature, dirTemp, 0.05f * dt, -15, 100);
        drift(sensorData.humidity, dirHumidity, 0.2f * dt, 0, 100);
        drift(sensorData.light, dirLight, 3.0f * dt, 0, 1000);
    }

    void applyDeviceEffects(SensorData& sensorData, const DeviceState& deviceState, float dt) {
        // 💧 Pompa: Nem artırır                    + soilMoisture, + humidity
        if (deviceState.isPumpOn()) {
            float moisture = sensorData.getSoilMoisture();
            float growth = (100.0f - moisture) * 0.15f * dt;
            float maxGrowth = 3.0f;  // sınırla
            if (growth > maxGrowth) growth = maxGrowth;

            sensorData.setSoilMoisture(moisture + growth);  // Toprak nemi artır → ama doygunluğa yaklaşınca artış yavaşlar

            float humidity = sensorData.getHumidity();
            sensorData.setHumidity(humidity + (moisture / 100.0f) * 0.2f * dt);     // Buharlaşma etkisiyle ortam nemi artar
        }

        // 🌬️ Fan: Sıcaklığı ve nemi düşürür        -temp, - humidity
        if (deviceState.isFanOn()) {
            float temp = sensorData.getTemperature();
            float tempEffect = (temp > 20.0f) ? 0.2f : 0.05f;        // Ortam sıcaklığı 20°C’nin altındaysa fan çok etki etmez
            sensorData.setTemperature(temp - tempEffect * dt);       // °C düşüş

            float humidity = sensorData.getHumidity();
            float humidityDrop = std::min(humidity, 60.0f) / 100.0f * 0.5f * dt;
            sensorData.setHumidity(humidity - humidityDrop);         // Fan nemi dağtırır → buharı uzaklaştırır           

            float soilMoisture = sensorData.getSoilMoisture();
            float soilMoistureDrop = std::min(soilMoisture, 60.0f) / 100.0f * 0.5f * dt;
            sensorData.setSoilMoisture(soilMoisture - soilMoistureDrop);         // Fan nemi dağtırır → buharı uzaklaştırır           
        }

        // 🔥 Isıtıcı: Sıcaklığı yükseltir          +temp, -humidity
        if (deviceState.isHeaterOn()) {
            float temp = sensorData.getTemperature();
            float thermalResistance = 1.0f + (temp - 15.0f) / 20.0f;
            sensorData.setTemperature(temp + (0.4f / thermalResistance) * dt);          // Ortam ısıtıcının etkisine karşı daha yavaş tepki verir (inertia)

            float humidity = sensorData.getHumidity();
            sensorData.setHumidity(humidity - 0.2f * dt);            // Isıtma → nemi düşürür (kurutur)
            float soilMoisture = sensorData.getSoilMoisture();
            sensorData.setSoilMoisture(soilMoisture - 0.2f * dt);
        }

        // 💡 Grow Light: Işık seviyesini sabit değerle yükseltir
        if (deviceState.isGrowLightOn()) {
            sensorData.setLight(400.0f); // sabit 400 lux etkisi
        } else {
            // Grow light kapalı → ortam zifiri karanlık
            sensorData.setLight(0.0f);
        }

        // Sınırları aşmasın
        clamp(sensorData.getSoilMoisture(), 0.0f, 100.0f);
        clamp(sensorData.getTemperature(), -15.0f, 100.0f);
        clamp(sensorData.getHumidity(), 0.0f, 100.0f);
        clamp(sensorData.getLight(), 0.0f, 1000.0f);
    }

    std::chrono::steady_clock::time_point lastUpdate;

    int dirSoil = 1, dirTemp = 1, dirHumidity = 1, dirLight = 1;

    void drift(float& val, int& dir, float delta, float minVal, float maxVal) {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> dist(0.0f, delta);
        float change = dist(rng) * dir;
        val += change;

        if (val < minVal || val > maxVal) {
            dir *= -1;
            val = clamp(val, minVal, maxVal);
        }
    }
};

#endif
