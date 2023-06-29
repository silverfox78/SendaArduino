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
  int center_x = 62;  //WIDTH/2;
  int center_y = 31;  //HEIGHT/2;
  int radius = 10;
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
  const float proximity_factor = 2.0;
  const float nullification_factor = 0.8;
  const int16_t centerCircle = isVertical ? center_y : center_x;
  // const int distance = floor(centerCircle > position ? centerCircle - position : position - centerCircle);

  // const int distanceMax = floor((centerCircle > position ? centerCircle - position : position - centerCircle) * proximity_factor);
  // const int distanceMin = floor((centerCircle > position ? centerCircle - position : position - centerCircle) * nullification_factor);

  const int16_t end_point = isVertical ? HEIGHT : WIDTH;
  const int16_t start_curve = centerCircle - (radius * proximity_factor);
  const int16_t end_curve = centerCircle + (radius * proximity_factor);

  for (int16_t i = 0; i < start_curve; i++) {
    display.drawPixel(isVertical ? position : i, isVertical ? i : position, WHITE);
  }

  for (int16_t i = end_curve + 1; i < end_point; i++) {
    display.drawPixel(isVertical ? position : i, isVertical ? i : position, WHITE);
  }

  const int16_t nullification_distance = radius * nullification_factor;
  const int h = floor(centerCircle > position ? centerCircle - position : position - centerCircle) - 2;
  const int curveDistance = end_curve - start_curve;
  int count = 0;
  for (int16_t i = start_curve; i < end_curve; i++) {
    int curveFactor = sin(PI * (count / curveDistance)); //floor(h * sin(PI * (count / curveDistance)));
    const int printPoint = i + curveFactor;
    const int distance = floor(centerCircle > printPoint ? centerCircle - printPoint : printPoint - centerCircle);
    Serial.print("Eje:");
    Serial.print(isVertical ? "Vertical" : "Horizontal");
    Serial.print(" - Pilar:");
    Serial.print(position);
        Serial.print(" - curveDistance:");
    Serial.print(curveDistance);
    Serial.print(" - curveFactor:");
    Serial.print(curveFactor);
    Serial.print(" - point:");
    Serial.print(i);
    Serial.print(" - count:");
    Serial.print(count);
    Serial.print(" - distance:");
    Serial.println(distance);
    if (distance >= nullification_distance) {
      display.drawPixel(isVertical ? position : printPoint, isVertical ? printPoint : position, WHITE);
    }
    count++;
  }
}