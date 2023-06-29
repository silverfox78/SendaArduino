#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>
#include <Arduino.h>

#define BAUD_RATE 9600
#define DELAYTIME 1000
#define WIDTH 128
#define HEIGHT 64
#define OLED_RESET 4

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(BAUD_RATE);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}

void loop() {
  display.clearDisplay();
  for (int16_t i = 0; i < WIDTH; i += 5) {
    drawLine(true, i);
  }

  for (int16_t i = 0; i < HEIGHT; i += 5) {
    drawLine(false, i);
  }
  display.display();
}

void drawLine(bool isVertical, int16_t position) {
  const int16_t end_point = isVertical ? HEIGHT : WIDTH;

  for (int16_t i = 0; i < end_point; i++) {
    display.drawPixel(isVertical ? position : i, isVertical ? i : position, WHITE);
  }
}

bool isCurveLine(int16_t center_x, int16_t center_y, int16_t radius, bool isVertical, int16_t position){
  const float proximity_factor = 2.0;
  const float nullification_factor = 0.8;

}