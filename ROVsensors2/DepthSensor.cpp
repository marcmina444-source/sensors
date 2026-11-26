
#include "DepthSensor.h"

DepthSensor::DepthSensor(float density,
                         float surfacePressureMbar) {

    waterDensity = density;
    surfacePressure = surfacePressureMbar;
}

bool DepthSensor::begin() {

    if (!sensor.init()) {
        Serial.println("MS5837 not found!");
        return false;
    }

    sensor.setModel(MS5837::MS5837_30BA);
    sensor.setFluidDensity(waterDensity);

    connected = true;

    Serial.println("MS5837 connected!");

    return true;
}

bool DepthSensor::readData() {

    if (!connected) return false;

    sensor.read();

    pressure = sensor.pressure();
    temperature = sensor.temperature();

    // Pressure difference: mbar to Pa
    // Depth = pressure difference / (density * gravity)
    depth = ((pressure - surfacePressure) * 100.0)
            / (waterDensity * 9.80665);

    return true;
}

void DepthSensor::printData() {

    if (!connected) return;

    Serial.println("\n--- DEPTH SENSOR DATA ---");

    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" mbar");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Depth: ");
    Serial.print(depth);
    Serial.println(" meters");
}

void DepthSensor::setWaterDensity(float density) {

    waterDensity = density;
    sensor.setFluidDensity(density);
}

void DepthSensor::setSurfacePressure(float pressureMbar) {

    surfacePressure = pressureMbar;
}

float DepthSensor::getDepth() {
    return depth;
}

float DepthSensor::getPressure() {
    return pressure;
}

float DepthSensor::getTemperature() {
    return temperature;
}
