
#ifndef BNO085_H
#define BNO085_H

#include <Wire.h>
#include <Adafruit_BNO08x.h>

class BNO085Sensor {

private:

    Adafruit_BNO08x bno;

    uint8_t address;
    const char* name;

    float qReal = 1.0;
    float qI = 0.0;
    float qJ = 0.0;
    float qK = 0.0;

    bool connected = false;
    bool hasData = false;

    unsigned long lastUpdate = 0;

    // Requested sensor reporting interval in microseconds
    uint32_t reportInterval = 10000;

public:

    BNO085Sensor(const char* sensorName, uint8_t sensorAddress);

    bool begin();
    bool readData();
    void printData();

    void setReportInterval(uint32_t interval);
};

#endif
