
#ifndef DEPTH_SENSOR_H
#define DEPTH_SENSOR_H

#include <Wire.h>
#include <MS5837.h>
class DepthSensor {
private:
    MS5837 sensor;
    bool connected = false;
    // Water density in kg/m^3
    float waterDensity = 1025.0;
    // Surface pressure in mbar
    float surfacePressure = 1013.25;
    float pressure = 0;
    float temperature = 0;
    float depth = 0;
public:
    DepthSensor(float density = 1025.0,
                float surfacePressureMbar = 1013.25);
    bool begin();
    bool readData();
    void printData();
    void setWaterDensity(float density);
    void setSurfacePressure(float pressureMbar)
    float getDepth();
    float getPressure();
    float getTemperature();
};
#endif
