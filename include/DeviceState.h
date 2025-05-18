#ifndef DEVICESTATE_H
#define DEVICESTATE_H

class DeviceState {
    friend class DeviceController;

public:
    bool isPumpOn() const { return pumpOn; }
    bool isFanOn() const { return fanOn; }
    bool isHeaterOn() const { return heaterOn; }
    bool isGrowLightOn() const { return growLightOn; }

private:
    DeviceState(bool pump = false, bool fan = false,
                bool heater = false, bool light = false)
        : pumpOn(pump), fanOn(fan), heaterOn(heater), growLightOn(light) {}

    void setPump(bool on) { pumpOn = on; }
    void setFan(bool on) { fanOn = on; }
    void setHeater(bool on) { heaterOn = on; }
    void setGrowLight(bool on) { growLightOn = on; }

    bool pumpOn = false;
    bool fanOn = false;
    bool heaterOn = false;
    bool growLightOn = false;
};

#endif
