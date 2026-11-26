
#ifndef LEAKAGE_SENSOR_H
#define LEAKAGE_SENSOR_H
class LeakageSensor {
private:
    int pin;
    // HIGH or LOW depending on the module's output
    int wetState;
    bool wet = false;
public:
    LeakageSensor(int sensorPin, int activeState = HIGH);
    void begin();
    bool readData();
    bool isWet();
    void printData();
};
#endif
