#include <Wire.h>
#include "clock.h"

#define BAUD_RATE 9600
#define DELAYTIME 1000
Clock clock;

void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);
}

void loop() {
  Serial.print(String(clock.getTime()));
  Serial.print(" - ");
  Serial.print(clock.getSecond());
  Serial.print(" - ");
  Serial.print(clock.getSecondPercentage());
  Serial.println("%");
  delay(DELAYTIME);
}
