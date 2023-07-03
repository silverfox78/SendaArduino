#include <Wire.h>
#include <MAX7219_Class.h>

#define BAUD_RATE 9600
#define DELAYTIME 1000

MAX7219_Class matriz;

void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);
  matriz.initialize(15);
}

void loop() {
  String text = "Ponyo";
  int len = text.length();
  for (int i = 0; i < len; i++) {
    matriz.printText(text.substring(0, i + 1).c_str());
    delay(DELAYTIME);
  }
}
