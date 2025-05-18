#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include "DeviceState.h"
#include <chrono>
#include <iostream>

class DeviceController {
public:
    int pumpDurationSec = 10;
    int fanDurationSec = 30;
    int heaterDurationSec = 30;

    std::chrono::steady_clock::time_point pumpActivated;
    std::chrono::steady_clock::time_point fanActivated;
    std::chrono::steady_clock::time_point heaterActivated;

    void setPump(bool on) {
        if (deviceState.isPumpOn() != on) {
            deviceState.setPump(on);
            if (on) pumpActivated = now();
            log("Pump", on);
        }
    }

    void setFan(bool on) {
        if (deviceState.isFanOn() != on) {
            deviceState.setFan(on);
            if (on) fanActivated = now();
            log("Fan", on);
        }
    }

    void setHeater(bool on) {
        if (deviceState.isHeaterOn() != on) {
            deviceState.setHeater(on);
            if (on) heaterActivated = now();
            log("Heater", on);
        }
    }

    void setGrowLight(bool on) {
        if (deviceState.isGrowLightOn() != on) {
            deviceState.setGrowLight(on);
            log("Grow Light", on);
        }
    }

    void updateTimers() {
        auto t = now();
        if (deviceState.isPumpOn() && elapsed(pumpActivated, t) > pumpDurationSec) {
            deviceState.setPump(false);
            logAuto("Pump");
        }
        if (deviceState.isFanOn() && elapsed(fanActivated, t) > fanDurationSec) {
            deviceState.setFan(false);
            logAuto("Fan");
        }
        if (deviceState.isHeaterOn() && elapsed(heaterActivated, t) > heaterDurationSec) {
            deviceState.setHeater(false);
            logAuto("Heater");
        }
    }

    void print() const {
        std::cout << "\n--- Device Status ---\n";
        std::cout << "Pump       : " << (deviceState.isPumpOn() ? "ON" : "OFF") << "\n";
        std::cout << "Fan        : " << (deviceState.isFanOn() ? "ON" : "OFF") << "\n";
        std::cout << "Heater     : " << (deviceState.isHeaterOn() ? "ON" : "OFF") << "\n";
        std::cout << "Grow Light : " << (deviceState.isGrowLightOn() ? "ON" : "OFF") << "\n";
    }

    const DeviceState& getDeviceState() const { return deviceState; }

private:
    DeviceState deviceState;

    std::chrono::steady_clock::time_point now() const {
        return std::chrono::steady_clock::now();
    }

    int elapsed(std::chrono::steady_clock::time_point start,
                std::chrono::steady_clock::time_point end) const {
        return std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    }

    void log(const std::string& name, bool on) const {
        std::cout << "[" << name << "] " << (on ? "ON" : "OFF") << "\n";
    }

    void logAuto(const std::string& name) const {
        std::cout << "[" << name << "] Auto turned OFF after timeout.\n";
    }
};

#endif
