
#include "BNO085.h"
BNO085Sensor::BNO085Sensor(const char* sensorName,
                           uint8_t sensorAddress)
    : bno(-1), address(sensorAddress), name(sensorName) {
}
bool BNO085Sensor::begin() {
    if (!bno.begin_I2C(address, &Wire)) {
        Serial.print(name);
        Serial.println(" not found!");
        return false;
    }
    if (!bno.enableReport(SH2_ROTATION_VECTOR, reportInterval)) {
        Serial.println("Could not enable IMU report!");
        return false;
    }
    connected = true;
    Serial.print(name);
    Serial.println(" connected!");
    return true;
}
bool BNO085Sensor::readData() {
    if (!connected) return false;
    sh2_SensorValue_t sensorValue;
    if (bno.getSensorEvent(&sensorValue)) {
        if (sensorValue.sensorId == SH2_ROTATION_VECTOR) {
            qReal = sensorValue.un.rotationVector.real;
            qI = sensorValue.un.rotationVector.i;
            qJ = sensorValue.un.rotationVector.j;
            qK = sensorValue.un.rotationVector.k;
            lastUpdate = millis();
            hasData = true;
            return true;
        }
    }
    return false;
}
void BNO085Sensor::printData() {
    if (!hasData) return;
    Serial.println("\n--- IMU DATA ---");
    Serial.print("Quaternion W: ");
    Serial.println(qReal, 4);
    Serial.print("Quaternion X: ");
    Serial.println(qI, 4);
    Serial.print("Quaternion Y: ");
    Serial.println(qJ, 4);
    Serial.print("Quaternion Z: ");
    Serial.println(qK, 4);
    Serial.print("Reading age: ");
    Serial.print(millis() - lastUpdate);
    Serial.println(" ms");
}
void BNO085Sensor::setReportInterval(uint32_t interval) {
   reportInterval = interval;
    // If already connected, enable the new reporting interval
    if (connected) {
        bno.enableReport(SH2_ROTATION_VECTOR, reportInterval);
    }
}