#ifndef MLed_h
#define MLed_h

#include <Arduino.h>

class MLed {
public:
  MLed();
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