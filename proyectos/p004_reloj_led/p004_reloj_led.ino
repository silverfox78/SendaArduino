#include <Wire.h>
#include "clock.h"
#include "mled.h"

#define BAUD_RATE 9600
#define DELAYTIME 1000

Clock clock;
MLed mled;
#define INTENSITY 2

void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);
  mled.initialize(INTENSITY);
}

void loop() {
  mled.printText(clock.getTime(), DELAYTIME);
}
