#include "Geometry.h"
#include <Arduino.h>

unsigned char max_width = 0;
unsigned char max_heigth = 0;
unsigned char base_x = 0;
unsigned char base_y = 0;

Geometry::Geometry() {
}

void Geometry::initialize(char width, char heigth, char x, char y) {
  max_width = width - 1;
  max_heigth = heigth - 1;
  base_x = x;
  base_y = y;
}

float Geometry::getSlope(unsigned char x, unsigned char y) {
  float slope = 0;
  if ((x - base_x) != 0) {
    slope = (float)(y - base_y) / (float)(x - base_x);
  }
  return slope;
}

int Geometry::getPointX(unsigned char x, unsigned char y, unsigned char point) {
  float slope = getSlope(x, y);
  float calculatedpoint;

  calculatedpoint = ((point - base_y) / slope) + base_x;
  if (calculatedpoint < 0 || calculatedpoint >= max_width) {
    return -1;
  }

  return floor(calculatedpoint);
}

int Geometry::getPointY(unsigned char x, unsigned char y, unsigned char point) {
  float slope = getSlope(x, y);
  float calculatedpoint;

  calculatedpoint = (slope * (point - base_x)) + base_y;
  if (calculatedpoint <= 0 || calculatedpoint >= max_width) { //max_heigth
    return -1;
  }
  
  return floor(calculatedpoint);
}

int Geometry::getFibonacci(int n) {
  if (n <= 1)
    return n;
  else
    return getFibonacci(n - 1) + getFibonacci(n - 2);
}