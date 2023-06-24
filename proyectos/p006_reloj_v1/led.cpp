#include "Led.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SSD1306_ADDRESS 0x3C
#define WIDTH 128
#define HEIGHT 64
#define OLED_RESET 4

Adafruit_SSD1306 oled(WIDTH, HEIGHT, &Wire, OLED_RESET);

Led::Led()
{
}

void Led::initialize()
{
    oled.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS);
    oled.setTextColor(WHITE);
}

void Led::clear()
{
    oled.clearDisplay();
    oled.setTextColor(WHITE);
}

void Led::measureText(int16_t& width, int16_t& height, const int size, const char* text)
{
  // bool oldDisplayState = oled.getDisplay();
  // oled.command(SSD1306_DISPLAYOFF);
  // oled.clearDisplay();
  oled.setTextSize(size);
  int16_t x, y;
  oled.getTextBounds(text, 0, 0, &x, &y, &width, &height);
  // if (oldDisplayState) {
  //   oled.command(SSD1306_DISPLAYON);
  // }
  // else {
  //   oled.command(SSD1306_DISPLAYOFF);
  // }
}

void Led::measureFormat(int16_t& width, int16_t& height, const int size, const char* format, ...)
{
  va_list args;
  va_start(args, format);

  int length = vsnprintf(nullptr, 0, format, args) + 1;
  char* buffer = new char[length];
  va_start(args, format);
  vsnprintf(buffer, length, format, args);
  va_end(args);

  // bool oldDisplayState = oled.getDisplay();
  // oled.command(SSD1306_DISPLAYOFF);
  // oled.clearDisplay();
  oled.setTextSize(size);
  int16_t x, y;
  oled.getTextBounds(buffer, 0, 0, &x, &y, &width, &height);
  // if (oldDisplayState) {
  //   oled.command(SSD1306_DISPLAYON);
  // }
  // else {
  //   oled.command(SSD1306_DISPLAYOFF);
  // }
  delete[] buffer;
}

void Led::printText(const int size, const int x, const int y, const char* text)
{
  oled.setCursor(x, y);
  oled.setTextSize(size);
  oled.print(text);
}

void Led::printFormat(const int size, const int x, const int y, const char* format, ...)
{
  va_list args;
  va_start(args, format);

  int length = vsnprintf(nullptr, 0, format, args) + 1;
  char* buffer = new char[length];
  va_start(args, format);
  vsnprintf(buffer, length, format, args);
  va_end(args);

  oled.setCursor(x, y);
  oled.setTextSize(size);
  oled.print(buffer);

  delete[] buffer;
}

void Led::display()
{
    oled.display();
}
