#include "SmartPotApp.h"
#include <thread>
#include <csignal>
#include <iostream>

SmartPotApp smartPotApp;

void onExit(int signum) {
    AppStateManager::save("save_state.txt", smartPotApp.profileManager.getSelectedProfile(), *smartPotApp.loopLogic.sensorController);
    std::cout << "\n[SmartPot] State saved. Exiting...\n";
    exit(signum);
}

int main() {
    smartPotApp.setup();
    std::signal(SIGINT, onExit); 
    std::signal(SIGTERM, onExit);
    
    while (true) {
        smartPotApp.loop(); // Arduino'daki loop()
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
