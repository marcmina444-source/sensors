
#include "LeakageSensor.h"
#include <Arduino.h>
LeakageSensor::LeakageSensor(int sensorPin, int activeState) {
    pin = sensorPin;
    wetState = activeState;
}
void LeakageSensor::begin() {
    pinMode(pin, INPUT);
    Serial.println("Leakage sensor initialized!");
}
bool LeakageSensor::readData() {
    int sensorValue = digitalRead(pin);
    wet = (sensorValue == wetState);
    return wet;
}
bool LeakageSensor::isWet() {
    return wet;
}
void LeakageSensor::printData() {
    Serial.println("\n--- LEAKAGE SENSOR DATA ---");
    if (wet) {
        Serial.println("WARNING: WATER DETECTED!");
    }
    else {
        Serial.println("No leakage detected.");
    }
}