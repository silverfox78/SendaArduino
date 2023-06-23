#include <Wire.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define BAUD_RATE 9600
#define DELAYTIME 100

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10
#define MAX_DEVICES 4

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);

  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 15);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  mx.clear();
}

void loop() {
  printText("Hola!!!", DELAYTIME);
}

void printText(const char* text, int delayTime) {
  mx.clear();

  int len = strlen(text);
  int total = len;

  uint8_t charWidth;
  uint8_t cBuf[8];
  for (int i = 0; i < len; i++) {
    charWidth = mx.getChar(text[i], sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
    total = total + charWidth;
  }

  for (int i = 0; i < len; i++) {    
    mx.setChar(total, text[i]);
    charWidth = mx.getChar(text[i], sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
    total = total - charWidth - 1;
    mx.update();
    delay(delayTime);
  }

  mx.clear();
  mx.update();

  delay(delayTime);
}