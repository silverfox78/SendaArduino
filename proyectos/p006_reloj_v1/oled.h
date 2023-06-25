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
  int calcularX(int x1, int y1, int x2, int y2, int y);
  int calcularY(int x1, int y1, int x2, int y2, int x);
};

#endif