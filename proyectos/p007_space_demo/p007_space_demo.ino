#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>
#include <Arduino.h>

#define BAUD_RATE 9600
#define DELAY_TIME 1000
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define OLED_RESET_PIN 4

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET_PIN);

void setup() {
  Serial.begin(BAUD_RATE);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}

void loop() {
  int center_x = 100;
  int center_y = 50;
  int initial_radius = 12;

  int total_x_decrease = 70;
  int total_y_decrease = 25;
  int total_radius_increase = 10;

  for(int percentage = 0; percentage <= 100; percentage += 5){
    display.clearDisplay();

    int x_decrease = static_cast<int>(total_x_decrease / 100.0 * percentage);
    int y_decrease = static_cast<int>(total_y_decrease / 100.0 * percentage);
    int radius_increase = static_cast<int>(total_radius_increase / 100.0 * percentage);

    int radius = initial_radius + radius_increase;

    drawCircle(center_x - x_decrease, center_y - y_decrease, radius / 2);
    drawShape(center_x - x_decrease, center_y - y_decrease, radius);

    display.display();
    delay(100);
  }  
}

void drawShape(int center_x, int center_y, int radius) {
  const int line_break = 6;

  for (int i = 0; i < DISPLAY_WIDTH; i += line_break) {
    if (evaluateLine(center_x, center_y, radius, i, false)) {
      curveLine(center_x, center_y, radius, i, false);
    } else {
      display.drawLine(i, 0, i, DISPLAY_HEIGHT - 1, WHITE);
    }
  }

  for (int i = 0; i < DISPLAY_HEIGHT; i += line_break) {
    if (evaluateLine(center_x, center_y, radius, i, true)) {
      curveLine(center_x, center_y, radius, i, true);
    } else {
      display.drawLine(0, i, DISPLAY_WIDTH - 1, i, WHITE);
    }
  }
}

bool evaluateLine(int center_x, int center_y, int radius, int line, bool is_vertical) {
  const float proximity_threshold = 2.5;

  int length = is_vertical ? DISPLAY_WIDTH : DISPLAY_HEIGHT;

  for (int j = 0; j < length; j++) {
    float distance_vector = calculateDistance(center_x, center_y, is_vertical ? j : line, is_vertical ? line : j);
    if (distance_vector <= radius * proximity_threshold) {
      return true;
    }
  }
  return false;
}

//v1
void curveLine(int center_x, int center_y, int radius, int line, bool is_vertical) {
  int start_pixel = -1;
  int end_pixel = -1;
  const float proximity_factor = 2.0;
  int length = is_vertical ? DISPLAY_WIDTH : DISPLAY_HEIGHT;

  for (int j = 0; j < length; j++) {
    float distance_vector = calculateDistance(center_x, center_y, is_vertical ? j : line, is_vertical ? line : j);
    if (distance_vector > radius * proximity_factor) {
      display.drawPixel(is_vertical ? j : line, is_vertical ? line : j, WHITE);
    } else {
      if (start_pixel == -1) {
        start_pixel = j;
      } else {
        end_pixel = j;
      }
    }
  }

  if (end_pixel == -1) {
    int delta = line < (is_vertical ? center_y : center_x) ? line - 1 : line + 1;
    display.drawPixel(is_vertical ? start_pixel : delta, is_vertical ? delta : start_pixel, WHITE);
    return;
  }

  float curve_value = calculateDistance(center_x, center_y, start_pixel, line) - 2;
  int h = curve_value - abs(is_vertical ? center_y - line : center_x - line);

  for (int j = start_pixel; j <= end_pixel; j++) {
    int point_y = floor(getYValue(j, start_pixel, end_pixel, (h / 3), (h / 2)));
    display.drawPixel(is_vertical ? j : (line < center_x ? line - point_y : line + point_y), 
                      is_vertical ? (line < center_y ? line - point_y : line + point_y) : j, WHITE);
  }
}

//v2
// void curveLine(int center_x, int center_y, int radius, int line, bool is_vertical) {
//   const float proximity_factor = 2.0;
//   const float curvature_factor = 0.01;  // Factor to control the amount of curvature
//   int length = is_vertical ? DISPLAY_WIDTH : DISPLAY_HEIGHT;

//   for (int j = 0; j < length; j++) {
//     float distance_vector = calculateDistance(center_x, center_y, is_vertical ? j : line, is_vertical ? line : j);
//     if (distance_vector <= radius * proximity_factor) {
//       int displacement = curvature_factor * pow(j - (is_vertical ? center_x : center_y), 2);
//       display.drawPixel(is_vertical ? j : line + displacement, is_vertical ? line + displacement : j, WHITE);
//     } else {
//       display.drawPixel(is_vertical ? j : line, is_vertical ? line : j, WHITE);
//     }
//   }
// }

//v3
// void curveLine(int center_x, int center_y, int radius, int line, bool is_vertical) {
//   const float proximity_factor = 2.0;
//   int length = is_vertical ? DISPLAY_WIDTH : DISPLAY_HEIGHT;
  
//   // Coordinates of points where line intersects the circle
//   int x1 = center_x - radius;
//   int x2 = center_x + radius;

//   // If line intersects circle, draw curved lines
//   if (line > center_y - radius && line < center_y + radius) {
//     // Draw line segments on either side of the circle
//     for (int i = 0; i < x1; i++) {
//       display.drawPixel(i, line, WHITE);
//     }
//     for (int i = x2; i < length; i++) {
//       display.drawPixel(i, line, WHITE);
//     }

//     // Draw curved lines around the circle
//     for (int i = x1; i <= x2; i++) {
//       // Use a sinusoidal function to get curve height, adjust amplitude and frequency as needed
//       int curveHeight = (int)(10 * sin(PI * (i - x1) / (x2 - x1)));
      
//       // Depending on which side of the center the line is, curve goes up or down
//       if (line < center_y) {
//         display.drawPixel(i, line - curveHeight, WHITE);
//       } else {
//         display.drawPixel(i, line + curveHeight, WHITE);
//       }
//     }
//   } else {
//     // If line does not intersect circle, draw straight line
//     for (int i = 0; i < length; i++) {
//       display.drawPixel(i, line, WHITE);
//     }
//   }
// }

float calculateDistance(int x1, int y1, int x2, int y2) {
  int dx = x2 - x1;
  int dy = y2 - y1;
  return sqrt(dx * dx + dy * dy);
}

void drawCircle(int16_t center_x, int16_t center_y, int16_t radius) {
  const int break_point = 5;
  int count = 0;
  for (float theta = 0; theta < 2 * PI; theta += 0.01) {
    if (count % break_point == 0) {
      int16_t x1 = center_x + radius * cos(theta);
      int16_t y1 = center_y + radius * sin(theta);
      int16_t x2 = center_x + radius * cos(theta + 0.01);
      int16_t y2 = center_y + radius * sin(theta + 0.01);
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
