#include <Wire.h>
#include "oled.h"

#define BAUD_RATE 9600
#define DELAYTIME 500

OLed oled;

void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);
  oled.initialize();
}

void loop() {
  oled.draw();
}
