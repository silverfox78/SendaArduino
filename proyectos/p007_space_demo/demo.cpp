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
  

  int centerX = 100;
  int centerY = 50;
  int radius = 12;

  int decXtotal = 70;
  int decYtotal = 25;
  int incRadioTotal = 10;
  for(int por = 0; por <= 100; por+=5){
    display.clearDisplay();
    int decX = (decXtotal/100.0) * por;
    int decY = (decYtotal/100.0) * por;
    int incRacio = (incRadioTotal/100.0) * por;
    drawCircle(centerX - decX, centerY - decY, ((radius + incRacio)/2));
    draw(centerX - decX, centerY - decY, radius + incRacio);
    display.display();
    delay(100);
  }  
}

void draw(int x, int y, int radio) {
  int breakLine = 6;
  for (int i = 0; i < 128; i += breakLine) {
    if (evaluateLineX(x, y, radio, i)) {
      curveLineX(x, y, radio, i);
    } else {
      display.drawLine(i, 0, i, 63, WHITE);
    }
  }

  for (int i = 0; i < 64; i += breakLine) {
    if (evaluateLineY(x, y, radio, i)) {
      curveLineY(x, y, radio, i);
    } else {
      display.drawLine(0, i, 127, i, WHITE);
    }
  }
}

bool evaluateLineX(int x, int y, int radio, int pilarX) {
  bool afectada = false;
  float prox = 2.5;
  for (int j = 0; j < 64; j++) {
    float vector = distancia(x, y, pilarX, j);
    if (vector <= radio * prox) {
      return true;
    }
  }
  return false;
}

bool evaluateLineY(int x, int y, int radio, int pilarY) {
  bool afectada = false;
  float prox = 2.5;
  for (int j = 0; j < 128; j++) {
    float vector = distancia(x, y, j, pilarY);
    if (vector <= radio * prox) {
      return true;
    }
  }
  return false;
}

void curveLineX(int x, int y, int radio, int pilarX) {
  int start = -1;
  int end = -1;
  float prox = 2;
  for (int j = 0; j < 64; j++) {
    float vector = distancia(x, y, pilarX, j);
    if (vector > radio * prox) {
      display.drawPixel(pilarX, j, WHITE);
    } else {
      if (start == -1) {
        start = j;
      } else {
        end = j;
      }
    }
  }

  if (end == -1) {
    int delta = pilarX < x ? pilarX - 1 : pilarX + 1;
    display.drawPixel(delta, start, WHITE);
    return;
  }

  float curva = distancia(x, y, pilarX, start) - 2;
  int h = curva - (x > pilarX ? x - pilarX : pilarX - x);

  int totalRec = y - start;
  int cont = 0;
  for (int j = start; j <= end; j++) {
    int punto_X = floor(getYValue(j, start, end, (h / 3), (h / 2)));
    display.drawPixel(pilarX < x ? pilarX - punto_X : pilarX + punto_X, j, WHITE);
  }
}

void curveLineY(int x, int y, int radio, int pilarY) {
  int start = -1;
  int end = -1;
  float prox = 2;
  for (int j = 0; j < 128; j++) {
    float vector = distancia(x, y, j, pilarY);
    if (vector > radio * prox) {
      display.drawPixel(j, pilarY, WHITE);
    } else {
      if (start == -1) {
        start = j;
      } else {
        end = j;
      }
    }
  }

  if (end == -1) {
    int delta = pilarY < y ? pilarY - 1 : pilarY + 1;
    display.drawPixel(start, delta, WHITE);
    return;
  }

  float curva = distancia(x, y, start, pilarY) - 2;
  int h = curva - (x > pilarY ? y - pilarY : pilarY - y);

  int totalRec = x - start;
  int cont = 0;
  for (int j = start; j <= end; j++) {
    int punto_Y = floor(getYValue(j, start, end, (h / 3), (h / 2)));
    display.drawPixel(j, pilarY < y ? pilarY - punto_Y : pilarY + punto_Y, WHITE);
  }
}

float distancia(int x1, int y1, int x2, int y2) {
  int dx = x2 - x1;
  int dy = y2 - y1;
  return sqrt(dx * dx + dy * dy);
}

void drawCircle(int16_t x, int16_t y, int16_t radius) {
  int break_point = 5;
  int count = 0;
  for (float theta = 0; theta < 2 * PI; theta += 0.01) {
    if (count % break_point == 0) {
      int16_t x1 = x + radius * cos(theta);
      int16_t y1 = y + radius * sin(theta);
      int16_t x2 = x + radius * cos(theta + 0.01);
      int16_t y2 = y + radius * sin(theta + 0.01);
      display.drawLine(x1, y1, x2, y2, WHITE);
    }
    count++;
  }
}

const double LOG_BASE = 24.0;

double func1(double x, double x1, double x2, double A) {
  double quarter = x1 + (x2 - x1) / 4;
  return A * (log10(x - x1 + 1) / log10(quarter - x1 + 1)) / log10(LOG_BASE);
}

double func2(double x, double x1, double x2, double A, double B) {
  double quarter = x1 + (x2 - x1) / 4;
  double threeQuarter = x1 + 3 * (x2 - x1) / 4;
  double mid = (quarter + threeQuarter) / 2;
  return -(B - A) * pow((x - mid) / (mid - quarter), 2) + B;
}

double func3(double x, double x1, double x2, double A) {
  double threeQuarter = x1 + 3 * (x2 - x1) / 4;
  return A * (log10(x2 - x + 1) / log10(x2 - threeQuarter + 1)) / log10(LOG_BASE);
}

double getYValue(double x, double x1, double x2, double A, double B) {
  double quarter = x1 + (x2 - x1) / 4;
  double threeQuarter = x1 + 3 * (x2 - x1) / 4;

  if (x < x1 || x > x2) {
    return -1;
  } else if (x <= quarter) {
    return func1(x, x1, x2, A);
  } else if (x <= threeQuarter) {
    return func2(x, x1, x2, A, B);
  } else {
    return func3(x, x1, x2, A);
  }
}
