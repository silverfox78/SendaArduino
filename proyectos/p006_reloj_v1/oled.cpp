
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

#define COUNT_OPTIONS 2

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
  }
}

void OLed::drawClear() {
  int delayDraw = 2;
  led.clear();

  for (int y = 0; y < 64; y++) {
    if (y % 2 == 0) {
      led.drawLine(0, y, 128, y);
      delay(delayDraw);
    }
  }
  led.display();

  for (int y = 0; y < 64; y++) {
    if (y % 2 != 0) {
      led.drawLine(0, y, 128, y);
      delay(delayDraw);
    }
  }
  led.display();
}

void OLed::drawClockInfo() {
  int delayDraw = 100;
  bool ifDraw = false;
  int endPrint = 20;

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

// void OLed::drawHorizont() {
//   int delayDraw = 5;
//   bool ifDraw = false;
//   int endPrint = 150;

//   if (millis() > (lastTime + delayDraw) || lastTime == 0) {
//     lastTime = millis();
//     ifDraw = true;
//     countPrints++;

//     if (countPrints >= endPrint) {
//       countPrints = 0;
//       requireChange = true;
//       led.clear();
//       led.display();
//     }
//   }

//   if (ifDraw) {
//     led.clear();
//     led.printText(2, 5, 5, clock.getTime());

//     int porcentaje = floor(countPrints * 100) / endPrint;

//     led.drawLine(1, 41, 126, 39);
//     led.drawLine(1, 42, 126, 40);

//     int radiusInc = (5 / 100.0) * porcentaje;
//     int radius = 5 + radiusInc;
//     int xInc = (95 / 100.0) * porcentaje;
//     int xCenter = 10 + xInc;
//     int alt = (25 / 100.0) * porcentaje;
//     int yCenter = 45 - alt;

//     int cont = 0;

//     for (int y = -radius; y <= radius; y += 2) {
//       int lineLength = sqrt(radius * radius - y * y);
//       int yScreen = yCenter + y;
//       if (yScreen < 40) {
//         led.drawLine(xCenter - lineLength, yScreen, xCenter + lineLength, yScreen);
//       }
//     }

//     if (yCenter <= 40) {
//       for (int x = 10; x <= 115; x += 5) {
//         int neoX = calcularX(xCenter, yCenter, x, 40, 63);
//         if (neoX <= -1) {
//           int neoY = 40;
//           if (x <= 62) {
//             neoY = calcularY(xCenter, yCenter, x, 40, 0);
//             if (neoY > 40) {
//               led.drawLine(x, 40, 0, neoY);
//             } else {
//               led.drawLine(x, 40, 0, 40 + (40 - neoY));
//             }
//           } else {
//             neoY = calcularY(xCenter, yCenter, x, 40, 123);
//             if (neoY > 40) {
//               led.drawLine(x, 40, 123, neoY);
//             } else {
//               led.drawLine(x, 40, 123, 40 + (40 - neoY));
//             }
//           }

//         } else {
//           led.drawLine(x, 40, neoX, 63);
//         }
//       }
//     }

//     led.display();
//   }
// }

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

void OLed::drawPiramid(int base, int altura, int x1, int suelo) {    
    int x2 = x1 + base;
    int y = suelo;
    
    int x3 = x1 + (base / 2);
    int y3 = y - altura;

    led.fillTriangle(x1, y, x2, y, x3, y3);
}