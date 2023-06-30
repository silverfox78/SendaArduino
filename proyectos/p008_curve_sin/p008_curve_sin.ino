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
  int center_x = 62;
  int center_y = 31;
  int radius = 10;

  drawCircle(center_x, center_y, radius);

  for (int i = 0; i < WIDTH; i += 5) {
    drawLine(center_x, center_y, radius, true, i);
  }

  for (int16_t i = 0; i < HEIGHT; i += 5) {
    drawLine(center_x, center_y, radius, false, i);
  }

  display.display();
}

void drawLine(int16_t center_x, int16_t center_y, int16_t radius, bool isVertical, int16_t position) {
  const int16_t end_point = isVertical ? HEIGHT : WIDTH;

  bool isCurve = isCurveLine(center_x, center_y, radius, isVertical, position);

  if (!isCurve) {
    for (int16_t i = 0; i < end_point; i++) {
      display.drawPixel(isVertical ? position : i, isVertical ? i : position, WHITE);
    }
  } else {
    drawCurveLine(center_x, center_y, radius, isVertical, position);
  }
}

bool isCurveLine(int16_t center_x, int16_t center_y, int16_t radius, bool isVertical, int16_t position) {
  const float proximity_factor = 2.0;
  const float nullification_factor = 0.8;
  const int16_t centerCircle = isVertical ? center_x : center_y;
  const int distance = floor(centerCircle > position ? centerCircle - position : position - centerCircle);
  return distance <= radius * proximity_factor;
}

void drawCurveLine(int16_t center_x, int16_t center_y, int16_t radius, bool isVertical, int16_t position) {
  const float proximity_factor = 2.5;
  const float nullification_factor = 0.8;
  const int16_t centerCircle = isVertical ? center_y : center_x;
  const int16_t end_point = isVertical ? HEIGHT : WIDTH;
  const int16_t start_curve = centerCircle - (radius * proximity_factor);
  const int16_t end_curve = centerCircle + (radius * proximity_factor);
  const int16_t curveDistance = end_curve - start_curve;
  for (int16_t i = 0; i < start_curve; i++) {
    display.drawPixel(isVertical ? position : i, isVertical ? i : position, WHITE);
  }

  for (int16_t i = end_curve + 1; i < end_point; i++) {
    display.drawPixel(isVertical ? position : i, isVertical ? i : position, WHITE);
  }

  const int16_t centerEje = isVertical ? center_x : center_y;
  const int16_t distance_position = centerEje > position ? centerEje - position : position - centerEje;
  const int16_t distance_extra = (radius * proximity_factor) - distance_position;
  const int16_t height_curve = floor((distance_extra / 100.0) * 60);
  const int16_t direction_curve = centerEje - position >= 0 ? -1 : 1;

  int count = 0;
  for (int16_t i = start_curve; i < end_curve; i++) {
    int curveFactor = direction_curve * (int)height_curve * sin(PI * count / curveDistance);
    int printPoint = position + curveFactor;
    display.drawPixel(isVertical ? printPoint : i, isVertical ? i : printPoint, WHITE);
    count++;
  }
}

void drawCircle(int16_t center_x, int16_t center_y, int16_t radius) {
  int count = 1;
  int percentage = 0;
  int x1, x2;
  bool print = false;
  for (int y = center_y - radius; y < center_y + radius; y++) {
    print = false;
    percentage = floor(count * 100) / (2 * radius);
    if (percentage <= 20 && y % 2 == 0) {
      print = true;
    }
    if (percentage > 20 && percentage <= 60 && y % 2 == 0) {
      print = true;
    }

    if (percentage > 60) {
      print = true;
    }

    if (print) {
      infoCircle(center_x, center_y, radius, y, x1, x2);
      display.drawLine(x1, y, x2, y, WHITE);
    }
    count++;
  }
}

void infoCircle(int centerX, int centerY, int radius, int valueY, int& x1, int& x2) {
  int x = 0;
  int y = radius;
  int p = 1 - radius;

  while (x <= y) {
    if (valueY == centerY + y || valueY == centerY - y) {
      x1 = centerX + x;
      x2 = centerX - x;
      break;
    }
    if (valueY == centerY + x || valueY == centerY - x) {
      x1 = centerX + y;
      x2 = centerX - y;
      break;
    }

    if (p < 0) {
      p += 2 * x + 3;
    } else {
      p += 2 * (x - y) + 5;
      y--;
    }
    x++;
  }
}
