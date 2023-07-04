#include <Wire.h>
#include <DS3231_Class.h>
#include <MAX7219_Class.h>
#include <SSD1306_CLass.h>

#define BAUD_RATE 9600
#define DELAYTIME 1000

DS3231_Class clock;
MAX7219_Class matriz;
SSD1306_CLass led;

void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);  
  matriz.initialize(15);
  led.initialize();
}

void loop() {
  Serial.print(String(clock.getTime()));
  Serial.print(" - ");
  Serial.print(clock.getSecond());
  Serial.print(" - ");
  Serial.print(clock.getSecondPercentage());
  Serial.println("%");

  String text = String(clock.getTime());
  int len = text.length();

  for (int i = 0; i < len; i++) {
    led.clear();
    int16_t width, height;

    matriz.printText(text.substring(0, i + 1).c_str());
    led.measureText(width, height, 3, text.substring(0, i + 1).c_str());
    led.printText(3, 64 - (width / 2), 32 - (height/2), text.substring(0, i + 1).c_str());

    led.drawLine(3, 1, 120, 1);
    led.drawLine(1, 3, 122, 3);

    led.drawLine(1, 60, 122, 60);
    led.drawLine(3, 62, 120, 62);

    led.drawLine(3, 1, 3, 62);
    led.drawLine(1, 3, 1, 60);

    led.drawLine(120, 1, 120, 62);
    led.drawLine(122, 3, 122, 60);

    led.fillTriangle(6, 6, 12, 6, 6, 12);
    led.fillTriangle(111, 6, 117, 6, 117, 12);
    led.fillTriangle(6, 51, 12, 57, 6, 57);
    led.fillTriangle(117, 51, 117, 57, 111, 57);
    led.display();
    delay(DELAYTIME / 5);
  }

  delay(DELAYTIME);
}
