#ifndef FIREBASESERVICE_H
#define FIREBASESERVICE_H

#include "SensorData.h"
#include "DeviceState.h"
#include "SettingsManager.h"
#include <cpr/cpr.h>
#include <sstream>
#include <iostream>

class FirebaseService {
public:
    FirebaseService(const SettingsManager& settings) {
        baseUrl = settings.getString("firebase_url", "");
        if (baseUrl.empty()) {
            std::cerr << "[Firebase] ERROR: firebase_url missing in settings.txt\n";
        } else if (baseUrl.back() != '/') {
            baseUrl += "/";
        }
    }

    void pushSensorData(const SensorData& data) {
        std::ostringstream json;
        json << "{"
             << "\"temperature\":" << data.getTemperature() << ","
             << "\"humidity\":" << data.getHumidity() << ","
             << "\"soilMoisture\":" << data.getSoilMoisture() << ","
             << "\"light\":" << data.getLight()
             << "}";

        std::string fullUrl = baseUrl + "sensors.json";

        auto res = cpr::Put(
            cpr::Url{fullUrl},
            cpr::Header{{"Content-Type", "application/json"}},
            cpr::Body{json.str()}
        );

        logResponse("pushSensorData", res);
    }

    void pushDeviceState(const DeviceState& state) {
        std::ostringstream json;
        json << "{"
             << "\"pumpOn\":" << (state.isPumpOn() ? "true" : "false") << ","
             << "\"fanOn\":" << (state.isFanOn() ? "true" : "false") << ","
             << "\"heaterOn\":" << (state.isHeaterOn() ? "true" : "false") << ","
             << "\"growLightOn\":" << (state.isGrowLightOn() ? "true" : "false")
             << "}";

        std::string fullUrl = baseUrl + "device.json";

        auto res = cpr::Put(
            cpr::Url{fullUrl},
            cpr::Header{{"Content-Type", "application/json"}},
            cpr::Body{json.str()}
        );

        logResponse("pushDeviceState", res);
    }

private:
    std::string baseUrl;

    void logResponse(const std::string& label, const cpr::Response& res) {
        if (res.status_code >= 200 && res.status_code < 300) {
            std::cout << "[Firebase] " << label << " ✅ OK\n";
        } else {
            std::cerr << "[Firebase] " << label << " ❌ Error: " << res.status_code
                      << "\nResponse: " << res.text << "\n";
        }
    }
};

#endif
