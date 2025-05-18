#ifndef AUTODECISIONENGINE_H
#define AUTODECISIONENGINE_H

#include "SensorController.h"
#include "DeviceController.h"
#include "PlantProfile.h"

class AutoDecisionEngine {
public:
    void evaluate(const SensorController& sensorController, DeviceController& deviceController, const PlantProfile& profile) {
        const auto& sensor = sensorController.getSensorData();

        // 💧 Pompa
        if (sensor.getSoilMoisture() < profile.getMinSoilMoisture()) {
            deviceController.setPump(true);
        } else if (sensor.getSoilMoisture() > profile.getMaxSoilMoisture()) {
            deviceController.setPump(false);
        }

        // 🌬️ Fan: sıcaklık veya nem yüksekse çalışsın
        if (sensor.getTemperature() > profile.getMaxTemperature() ||
            sensor.getHumidity() > profile.getMaxHumidity()) {
            deviceController.setFan(true);
        } else if (sensor.getTemperature() < profile.getMaxTemperature() - 1.0f &&
                   sensor.getHumidity() < profile.getMaxHumidity() - 5.0f) {
            deviceController.setFan(false);
        }

        // 🔥 Isıtıcı
        if (sensor.getTemperature() < profile.getMinTemperature()) {
            deviceController.setHeater(true);
        } else if (sensor.getTemperature() > profile.getMinTemperature() + 1.0f) {
            deviceController.setHeater(false);
        }

        // 💡 Grow Light (anlık ışık kontrolü)
        if (sensor.getLight() < profile.getMinLight()) {
            deviceController.setGrowLight(true);
        } 
        
        // 🎯 (Opsiyonel) Günlük ışık süresi takibi yapılacaksa burada kontrol edilir
        // örn: lightHoursReached < profile.getRequiredLightHours() ? growLightOn = true;
    }
};


#endif
