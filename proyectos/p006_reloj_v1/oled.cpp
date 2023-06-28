
#include "OLed.h"
#include <Arduino.h>
#include <stdlib.h>
#include "clock.h"
#include "led.h"
#include "enum.h"
#include "geometry.h"

Clock clock;
Led led;
Geometry geometry;

#define COUNT_OPTIONS 3

unsigned long lastTime = 0;

int16_t countPrints = 0;
bool requireChange = true;
DrawOption option;
int lastOption = -1;

OLed::OLed() {
}

void OLed::initialize() {
  led.initialize();
}

DrawOption OLed::getRandomDrawOption() {
  int randomNumber = -1;
  do {
    randomNumber = random(0, COUNT_OPTIONS);
  } while (randomNumber == lastOption);
  lastOption = randomNumber;
  return static_cast<DrawOption>(randomNumber);
}

void OLed::draw() {
  if (requireChange) {
    option = getRandomDrawOption();
    requireChange = false;
    drawClear();
  }

  switch (option) {
    case CLOCK:
      drawClockInfo();
      break;
    case HORIZONT:
      drawHorizont();
      break;
    case SPACE:
      drawCurveSpace();
      break;
  }
}

void OLed::drawClear() {
  led.clear();
  delay(500);
  led.display();
}

void OLed::drawClockInfo() {
  int delayDraw = 100;
  bool ifDraw = false;
  int endPrint = 100;

  if (millis() > (lastTime + delayDraw) || lastTime == 0) {
    lastTime = millis();
    ifDraw = true;
    countPrints++;

    if (countPrints >= endPrint) {
      countPrints = 0;
      requireChange = true;
    }
  }

  if (ifDraw) {
    led.clear();
    int16_t width, height;
    led.measureFormat(width, height, 3, "%d%%", clock.getSecondPercentage());
    led.clear();
    led.printText(2, 5, 5, clock.getTime());
    led.printFormat(1, 5, 25, "%s seg", clock.getSecond());
    led.printFormat(3, 123 - width, 60 - height, "%d%%", clock.getSecondPercentage());
    led.display();
  }
}

void OLed::drawHorizont() {
  int delayDraw = 25;
  bool ifDraw = false;
  int endPrint = 80;

  if (millis() > (lastTime + delayDraw) || lastTime == 0) {
    lastTime = millis();
    ifDraw = true;
    countPrints++;

    if (countPrints >= endPrint) {
      countPrints = 0;
      requireChange = true;
      led.clear();
      led.display();
    }
  }

  if (ifDraw) {
    led.clear();
    led.printText(2, 5, 5, clock.getTime());

    int porcentaje = floor(countPrints * 100) / endPrint;
    int radiusInc = (7 / 100.0) * porcentaje;
    int radius = 5 + radiusInc;
    int xInc = (100 / 100.0) * porcentaje;
    int xCenter = 15 + xInc;
    int alt = (25 / 100.0) * porcentaje;
    int yCenter = 39 - alt;

    int cont = 0;

    for (int y = -radius; y <= radius; y += 2) {
      int lineLength = sqrt(radius * radius - y * y);
      int yScreen = yCenter + y;
      if (yScreen < 40) {
        led.drawLine(xCenter - lineLength, yScreen, xCenter + lineLength, yScreen);
      }
    }

    geometry.initialize(128, 64, xCenter, yCenter);

    int r = 40;
    for (int f = 0; f < 12; f++) {
      r += f * 2;
      if (r < 63) {
        led.drawLine(0, r, 127, r + f);
      }
    }

    int movePiramid = (60 / 100.0) * porcentaje;
    drawPiramid(8, 7, 90 - movePiramid, 39);
    drawPiramid(10, 9, 95 - movePiramid, 39);
    drawPiramid(12, 11, 100 - movePiramid, 39);
    drawPiramid(8, 8, 108 - movePiramid, 39);
    drawPiramid(13, 14, 112 - movePiramid, 39);
    drawPiramid(10, 10, 124 - movePiramid, 39);
    unsigned char lineHorizont = 40;
    unsigned char lineBottom = 63;
    int pointX = 0;
    int pointY = 0;

    for (int x = 5; x <= 120; x += 4) {
      pointX = geometry.getPointX(x, lineHorizont, lineBottom);
      pointY = lineBottom;

      if (pointX < 0) {
        if (geometry.getSlope(x, lineHorizont) == 0) {
          pointX = x;
        } else {
          pointX = geometry.getSlope(x, lineHorizont) < 0 ? 0 : 127;
          pointY = geometry.getPointY(x, lineHorizont, pointX);
        }
      }

      led.drawLine(x, lineHorizont, pointX, pointY);
    }

    led.display();
  }
}

void OLed::drawCurveSpace() {
  int delayDraw = 50;
  bool ifDraw = false;
  int endPrint = 35;

  if (millis() > (lastTime + delayDraw) || lastTime == 0) {
    lastTime = millis();
    ifDraw = true;
    countPrints++;

    if (countPrints >= endPrint) {
      countPrints = 0;
      requireChange = true;
      led.clear();
      led.display();
    }
  }

  if (ifDraw) {
    int porcentaje = floor(countPrints * 100) / endPrint;
    int incX = (80 / 100.0) * porcentaje;
    int incRadio = (4 / 100.0) * porcentaje;
    
    float a = -0.0002;
    float b = 55;
    float c = 40;
    float d = -0.65;
    int x = 20 + incX;
    int y = floor(a * ((d * x + b) * (d * x + b) * (d * x + b)) + c);
    int radio = 20;
    drawSpace(x, y, radio - incRadio , 2);
    led.display();
  }
}

void OLed::drawPiramid(int base, int altura, int x1, int suelo) {
  int x2 = x1 + base;
  int y = suelo;

  int x3 = x1 + (base / 2);
  int y3 = y - altura;

  led.fillTriangle(x1, y, x2, y, x3, y3);
}

void OLed::drawSpace(int16_t x, int16_t y, int16_t radio, int16_t break_point) {
  led.clear();

  int16_t start_width = 0;
  int16_t end_width = 128;

  int16_t start_heigth = 0;
  int16_t end_heigth = 64;

  drawCircle(x, y, radio - 4);

  for (int i = 0; i <= radio; i += break_point) {
    int16_t x1 = x + i;
    int16_t y1 = y - radio;
    int16_t x2 = x + radio;
    int16_t y2 = y - radio + i;

    drawLineToMargins(x1, y1, x2, y2);
  }

  for (int i = 0; i <= radio; i += break_point) {
    int16_t x1 = x + radio;
    int16_t y1 = y + i;
    int16_t x2 = x + radio - i;
    int16_t y2 = y + radio;

    drawLineToMargins(x1, y1, x2, y2);
  }

  for (int i = 0; i <= radio; i += break_point) {
    int16_t x1 = x - i;
    int16_t y1 = y + radio;
    int16_t x2 = x - radio;
    int16_t y2 = y + radio - i;

    drawLineToMargins(x1, y1, x2, y2);
  }

  for (int i = 0; i <= radio; i += break_point) {
    int16_t x1 = x - radio;
    int16_t y1 = y - i;
    int16_t x2 = x - radio + i;
    int16_t y2 = y - radio;

    drawLineToMargins(x1, y1, x2, y2);
  }
  led.display();
}

void OLed::drawCircle(int16_t x, int16_t y, int16_t radius) {
  int break_point = 5;
  int count = 0;
  for (float theta = 0; theta < 2 * PI; theta += 0.01) {
    if (count % break_point == 0) {
      int16_t x1 = x + radius * cos(theta);
      int16_t y1 = y + radius * sin(theta);
      int16_t x2 = x + radius * cos(theta + 0.01);
      int16_t y2 = y + radius * sin(theta + 0.01);
      led.drawLine(x1, y1, x2, y2);
    }
    count++;
  }
}

void OLed::drawLineToMargins(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  int OLED_WIDTH = 127;
  int OLED_HEIGHT = 63;
  int16_t startX, startY, endX, endY;

  geometry.initialize(OLED_WIDTH, OLED_HEIGHT, x1, y1);
  float slope = geometry.getSlope(x2, y2);

  if (slope == 0) {
    if (x1 == x2) {
      startX = int(x1);
      startY = 1;
      endX = int(x1);
      endY = OLED_HEIGHT;
    }

    if (y1 == y2) {
      startX = 1;
      startY = int(y1);
      endX = OLED_WIDTH;
      endY = int(y1);
    }
  } else {
    startX = geometry.getPointX(x2, y2, 1);
    startY = 1;
    endX = geometry.getPointX(x2, y2, OLED_WIDTH);
    endY = OLED_WIDTH;

    if (startX < 0) {
      startX = slope < 0 ? OLED_WIDTH : 1;
      startY = geometry.getPointY(x2, y2, startX);
    }

    if (endX < 0) {
      endX = slope < 0 ? 1 : OLED_WIDTH;
      endY = geometry.getPointY(x2, y2, endX);
    }
  }

  // Serial.print("Base A[");
  // Serial.print(x1);
  // Serial.print(",");
  // Serial.print(y1);
  // Serial.print("] || B[");
  // Serial.print(x2);
  // Serial.print(",");
  // Serial.print(y2);
  // Serial.print("] Pendiente:");
  // Serial.print(slope);
  // Serial.print(" || A(");
  // Serial.print(startX);
  // Serial.print(",");
  // Serial.print(startY);
  // Serial.print(") || B(");
  // Serial.print(endX);
  // Serial.print(",");
  // Serial.print(endY);
  // Serial.println(")");

  led.drawLine(startX, startY, endX, endY);
}