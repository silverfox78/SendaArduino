#ifndef OLed_h
#define OLed_h

#include <Arduino.h>
#include "enum.h"

class OLed {
public:
  OLed();
  void initialize();
  void draw();

private:
  DrawOption getRandomDrawOption();
  void drawClear();
  void drawClockInfo();
  void drawHorizont();
  void drawPiramid(int base, int altura, int x1, int suelo);
};

#endif