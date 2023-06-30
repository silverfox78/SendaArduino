#ifndef Led_h
#define Led_h

#include <Arduino.h>

class Led {
public:
  Led();
  void initialize();
  void clear();
  void measureText(int16_t& width, int16_t& height, const int size, const char* text);
  void measureFormat(int16_t& width, int16_t& height, const int size, const char* format, ...);
  void printText(const int size, const int x, const int y, const char* text);
  void printFormat(const int size, const int x, const int y, const char* format, ...);
  void drawLine(int x, int y, int end_x, int end_y);
  void drawPixel(int x, int y);
  void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
  void display();
};

#endif


// SSD1306      Arduino UNO
// ------------------------
// VCC          5V
// GND          GND
// SDA          A4
// SCL          A5