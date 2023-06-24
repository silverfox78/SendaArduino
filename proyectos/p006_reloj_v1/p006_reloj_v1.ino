#include <Wire.h>
#include "clock.h"
#include "mled.h"
#include "led.h"

#define BAUD_RATE 9600
#define DELAYTIME 500

Clock clock;
MLed mled;
Led led;
#define INTENSITY 2

void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);
  mled.initialize(INTENSITY);
  led.initialize();
}

void loop() {
  led.clear();
  int16_t width, height;
  led.measureFormat(width, height, 3, "%d%%", clock.getSecondPercentage());
  led.clear();
  led.printText(2, 5, 5, clock.getTime());
  led.printFormat(1, 5, 25, "%s seg", clock.getSecond());
  led.printFormat(3, 123 - width, 60 - height, "%d%%", clock.getSecondPercentage());
  led.display();
  delay(1000);
  //mled.printText(clock.getTime(), DELAYTIME);
}
