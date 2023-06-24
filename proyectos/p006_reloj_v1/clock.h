#ifndef Clock_h
#define Clock_h

#include <Arduino.h>

class Clock {
public:
  Clock();
  char* getTime();
  char* getSecond();
  int getSecondPercentage();

private:
  byte convert(byte val);
};

#endif

// DS3231       Arduino UNO
// ------------------------
// VCC          5V
// GND          GND
// SDA          A4
// SCL          A5