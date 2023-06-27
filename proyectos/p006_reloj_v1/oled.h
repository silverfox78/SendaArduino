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
  void drawCurveSpace();
  void drawPiramid(int base, int altura, int x1, int suelo);
  void drawCircle(int16_t x, int16_t y, int16_t radius);
  void drawLineToMargins(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
  void drawSpace(int16_t x, int16_t y, int16_t radio, int16_t break_point);
};

#endif