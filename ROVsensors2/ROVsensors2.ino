
#include <Wire.h>
#include "BNO085.h"
#include "DepthSensor.h"
#include "LeakageSensor.h"
// ==================================
// SETTINGS
// ==================================
const int SDA_PIN = 21;
const int SCL_PIN = 22;
const uint8_t IMU_ADDRESS = 0x4A;
const int LEAKAGE_PIN = 27;
const int LEAKAGE_ACTIVE_STATE = HIGH;
const unsigned long PRINT_INTERVAL = 500;

// ==================================
// SENSOR OBJECTS
// ==================================

BNO085Sensor imu("ROV IMU", IMU_ADDRESS);
DepthSensor depthSensor(1025.0, 1013.25);
LeakageSensor leakageSensor(
    LEAKAGE_PIN,
    LEAKAGE_ACTIVE_STATE
);
// ==================================
// SETUP
// ==================================
void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
    Wire.setClock(400000);
    imu.begin();
    depthSensor.begin();
    leakageSensor.begin();
}
// ==================================
// LOOP
// ==================================
void loop() {
    imu.readData();
    depthSensor.readData();
    leakageSensor.readData();
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint >= PRINT_INTERVAL) {
        lastPrint = millis();
        imu.printData();
        depthSensor.printData();
        leakageSensor.printData();
    }
}
