#include <Wire.h>
#include <DS3231_Class.h>

#define BAUD_RATE 9600
#define DELAYTIME 1000

DS3231_Class clock;

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
