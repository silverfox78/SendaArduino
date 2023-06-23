#include "Clock.h"
#include <Wire.h>

#define DS3231_ADDRESS 0x68

Clock::Clock() {
}

byte Clock::convert(byte val) {
  return (val / 16 * 10) + (val % 16);
}

char* Clock::getTime() {
  static char c_time[6];

  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 3);

  if (Wire.available() >= 3) {
    byte second = convert(Wire.read() & 0x7F);
    byte minute = convert(Wire.read());
    byte hour = convert(Wire.read() & 0x3F);

    sprintf(c_time, "%02d:%02d", hour, minute);
  } else {
    c_time[0] = '\0';
  }

  return c_time;
}

char* Clock::getSecond() {
  static char c_time[3];

  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 1);

  if (Wire.available()) {
    byte second = convert(Wire.read() & 0x7F);

    sprintf(c_time, "%02d", second);
  } else {
    c_time[0] = '\0';
  }

  return c_time;
}

int Clock::getSecondPercentage() {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 7);

  if (Wire.available()) {
    byte second = convert(Wire.read() & 0x7F);

    int percentage = map(second, 0, 59, 0, 100);

    return percentage;
  }
  
  return -1;
}
