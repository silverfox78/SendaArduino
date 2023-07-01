#ifndef DS3231_Class_h
#define DS3231_Class_h

#include <Arduino.h>

class DS3231_Class
{
public:
    DS3231_Class();
    char* getTime();
    char* getSecond();
    int getSecondPercentage();

private:
    void startWireTransmission();
    uint8_t convert(uint8_t val);
};

#endif

// DS3231       Arduino UNO
// ------------------------
// VCC          5V
// GND          GND
// SDA          A4
// SCL          A5