//SSD1306_CLass
#include "SSD1306_CLass.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SSD1306_ADDRESS 0x3C
#define WIDTH 128
#define HEIGHT 64
#define OLED_RESET 4

Adafruit_SSD1306 screen_oled(WIDTH, HEIGHT, &Wire, OLED_RESET);

SSD1306_CLass::SSD1306_CLass() {
}

void SSD1306_CLass::initialize() {
  screen_oled.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS);
  screen_oled.setTextColor(WHITE);
}

void SSD1306_CLass::clear() {
  screen_oled.clearDisplay();
  screen_oled.setTextColor(WHITE);
}

void SSD1306_CLass::measureText(int16_t& width, int16_t& height, const int size, const char* text) {
  screen_oled.setTextSize(size);
  int16_t x, y;
  screen_oled.getTextBounds(text, 0, 0, &x, &y, &width, &height);
}

void SSD1306_CLass::measureFormat(int16_t& width, int16_t& height, const int size, const char* format, ...) {
  va_list args;
  va_start(args, format);

  int length = vsnprintf(nullptr, 0, format, args) + 1;
  char* buffer = new char[length];
  va_start(args, format);
  vsnprintf(buffer, length, format, args);
  va_end(args);

  screen_oled.setTextSize(size);
  int16_t x, y;
  screen_oled.getTextBounds(buffer, 0, 0, &x, &y, &width, &height);
  delete[] buffer;
}

void SSD1306_CLass::printText(const int size, const int x, const int y, const char* text) {
  screen_oled.setCursor(x, y);
  screen_oled.setTextSize(size);
  screen_oled.print(text);
}

void SSD1306_CLass::printFormat(const int size, const int x, const int y, const char* format, ...) {
  va_list args;
  va_start(args, format);

  int length = vsnprintf(nullptr, 0, format, args) + 1;
  char* buffer = new char[length];
  va_start(args, format);
  vsnprintf(buffer, length, format, args);
  va_end(args);

  screen_oled.setCursor(x, y);
  screen_oled.setTextSize(size);
  screen_oled.print(buffer);

  delete[] buffer;
}

void SSD1306_CLass::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
  screen_oled.fillTriangle(x1, y1, x2, y2, x3, y3, WHITE);
}

void SSD1306_CLass::drawLine(int x, int y, int end_x, int end_y) {
  screen_oled.drawLine(x, y, end_x, end_y, WHITE);
}

void SSD1306_CLass::drawPixel(int x, int y) {
  screen_oled.drawPixel(x, y, WHITE);
}

void SSD1306_CLass::display() {
  screen_oled.display();
}
