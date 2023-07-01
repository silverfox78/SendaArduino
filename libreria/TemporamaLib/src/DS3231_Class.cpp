#include "DS3231_Class.h"
#include <Wire.h>
#include <Arduino.h>

#define DS3231_ADDRESS 0x68

DS3231_Class::DS3231_Class() {
}

uint8_t DS3231_Class::convert(uint8_t val) {
  return (val / 16 * 10) + (val % 16);
}

void DS3231_Class::startWireTransmission() {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
}

char* DS3231_Class::getTime() {
  static char c_time[6];

  startWireTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 3);

  uint8_t second = Wire.read() & 0x7F;
  uint8_t minute = Wire.read();
  uint8_t hour = Wire.read() & 0x3F;

  if (second != -1 && minute != -1 && hour != -1) {
    sprintf(c_time, "%02d:%02d", convert(hour), convert(minute));
  } else {
    c_time[0] = '\0';
  }

  return c_time;
}

char* DS3231_Class::getSecond() {
  static char c_time[3];

  startWireTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 1);

  uint8_t second = Wire.read() & 0x7F;

  if (second != -1) {
    sprintf(c_time, "%02d", convert(second));
  } else {
    c_time[0] = '\0';
  }

  return c_time;
}

int DS3231_Class::getSecondPercentage() {
  startWireTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 1);

  uint8_t second = Wire.read() & 0x7F;

  if (second != -1) {
    int percentage = map(convert(second), 0, 59, 0, 100);
    return percentage;
  }
  
  return -1;
}
