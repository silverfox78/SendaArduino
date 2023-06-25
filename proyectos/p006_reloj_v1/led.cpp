#include "Led.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SSD1306_ADDRESS 0x3C
#define WIDTH 128
#define HEIGHT 64
#define OLED_RESET 4

Adafruit_SSD1306 screen_oled(WIDTH, HEIGHT, &Wire, OLED_RESET);

Led::Led() {
}

void Led::initialize() {
  screen_oled.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS);
  screen_oled.setTextColor(WHITE);
}

void Led::clear() {
  screen_oled.clearDisplay();
  screen_oled.setTextColor(WHITE);
}

void Led::measureText(int16_t& width, int16_t& height, const int size, const char* text) {
  // bool oldDisplayState = screen_oled.getDisplay();
  // screen_oled.command(SSD1306_DISPLAYOFF);
  // screen_oled.clearDisplay();
  screen_oled.setTextSize(size);
  int16_t x, y;
  screen_oled.getTextBounds(text, 0, 0, &x, &y, &width, &height);
  // if (oldDisplayState) {
  //   screen_oled.command(SSD1306_DISPLAYON);
  // }
  // else {
  //   screen_oled.command(SSD1306_DISPLAYOFF);
  // }
}

void Led::measureFormat(int16_t& width, int16_t& height, const int size, const char* format, ...) {
  va_list args;
  va_start(args, format);

  int length = vsnprintf(nullptr, 0, format, args) + 1;
  char* buffer = new char[length];
  va_start(args, format);
  vsnprintf(buffer, length, format, args);
  va_end(args);

  // bool oldDisplayState = screen_oled.getDisplay();
  // screen_oled.command(SSD1306_DISPLAYOFF);
  // screen_oled.clearDisplay();
  screen_oled.setTextSize(size);
  int16_t x, y;
  screen_oled.getTextBounds(buffer, 0, 0, &x, &y, &width, &height);
  // if (oldDisplayState) {
  //   screen_oled.command(SSD1306_DISPLAYON);
  // }
  // else {
  //   screen_oled.command(SSD1306_DISPLAYOFF);
  // }
  delete[] buffer;
}

void Led::printText(const int size, const int x, const int y, const char* text) {
  screen_oled.setCursor(x, y);
  screen_oled.setTextSize(size);
  screen_oled.print(text);
}

void Led::printFormat(const int size, const int x, const int y, const char* format, ...) {
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

void Led::drawLine(int x, int y, int end_x, int end_y) {
  screen_oled.drawLine(x, y, end_x, end_y, WHITE);
}

void Led::display() {
  screen_oled.display();
}
