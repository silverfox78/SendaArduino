#ifndef Geometry_h
#define Geometry_h

#include <Arduino.h>

class Geometry {
public:
  Geometry();
  void initialize(char width, char heigth, char x, char y);
  float getSlope(unsigned char x, unsigned char y);
  int getPointX(unsigned char x, unsigned char y, unsigned char point);
  int getPointY(unsigned char x, unsigned char y, unsigned char point);
  int getFibonacci(int n);
};

#endif