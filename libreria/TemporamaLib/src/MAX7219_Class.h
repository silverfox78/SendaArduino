#ifndef MAX7219_Class_h
#define MAX7219_Class_h

#include <Arduino.h>

class MAX7219_Class {
public:
  MAX7219_Class();
  void initialize(int intensity);
  void printText(const char* text, int delayTime);  
};

#endif


// | MAX7219  | Arduino UNO |
// |----------|-------------|
// | VCC      | 5V          |
// | GND      | GND         |
// | CLK_PIN  | 13          |
// | DATA_PIN | 11          |
// | CS_PIN   | 10          |