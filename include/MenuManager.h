#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <iostream>
#include <limits>
#include "SensorController.h"
#include "DeviceController.h"
#include "PlantProfileManager.h"

class MenuManager {
public:

    static void showStatus(const SensorController& sensorController, const PlantProfile& profile, const DeviceController& deviceController) {
        const auto& sensorData = sensorController.getSensorData();
        const auto& deviceState = deviceController.getDeviceState();

        std::cout << "\n==============================\n";
        std::cout << "     Smart Pot Status\n";
        std::cout << "==============================\n";

        std::cout << "\nSensor Readings:\n";
        std::cout << "Soil Moisture : " << sensorData.getSoilMoisture() << " %\n";
        std::cout << "Temperature   : " << sensorData.getTemperature() << " C\n";
        std::cout << "Humidity      : " << sensorData.getHumidity() << " %\n";
        std::cout << "Light Level   : " << sensorData.getLight() << " lux\n";

        std::cout << "\n Selected Plant Profile: " << profile.getName() << "\n";
        std::cout << " - Min Moisture : " << profile.getMinSoilMoisture() << " %\n";
        std::cout << " - Temp Range   : " << profile.getMinTemperature() << " - "
                << profile.getMaxTemperature() << " C\n";
        std::cout << " - Min Light    : " << profile.getMinLight() << " lux\n";

        std::cout << "\n Device Status:\n";
        std::cout << "Pump       : " << (deviceState.isPumpOn() ? "ON" : "OFF") << "\n";
        std::cout << "Fan        : " << (deviceState.isFanOn() ? "ON" : "OFF") << "\n";
        std::cout << "Heater     : " << (deviceState.isHeaterOn() ? "ON" : "OFF") << "\n";
        std::cout << "Grow Light : " << (deviceState.isGrowLightOn() ? "ON" : "OFF") << "\n";
    }



    static void showMenu() {
        std::cout << "\n==== Menu ====\n";
        std::cout << "1. Refresh data\n";
        std::cout << "2. Show detailed device status\n";
        std::cout << "3. Run auto control\n";
        std::cout << "4. Select plant profile\n";
        std::cout << "0. Exit\n";
        std::cout << "Your choice: ";
    }

    static int getChoice() {
        int choice;
        std::cin >> choice;

        // Hatalı giriş olursa temizle ve tekrar sor
        while (std::cin.fail()) {
            std::cin.clear(); // Hata bayrağını sıfırla
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Geçersiz girdiyi atla
            std::cout << "Invalid input. Please enter a number: ";
            std::cin >> choice;
        }
        return choice;
    }

    static void clearScreen() {
        std::cout << std::string(50, '\n');
    }

};

#endif