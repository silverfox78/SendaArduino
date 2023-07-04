#include <Wire.h>
#include <SSD1306_CLass.h>

#define BAUD_RATE 9600
#define DELAYTIME 1000

SSD1306_CLass led;

void setup()
{
    Wire.begin();
    Serial.begin(BAUD_RATE);
    led.initialize();
}

void loop()
{
    led.clear();
    char* text = "Ponyo";

    int16_t width, height, height_last;
    led.measureText(width, height, 1, text);
    led.printText(1, 64 - (width/2), 8, text);
    height_last = height;

    led.measureText(width, height, 2, text);
    led.printText(2, 64 - (width/2), height_last + 6, text);
    height_last = height;

    led.measureText(width, height, 3, text);
    led.printText(3, 64 - (width/2), height_last + 15, text);

    led.drawLine(3, 1, 120, 1);
    led.drawLine(1, 3, 122, 3);

    led.drawLine(1, 60, 122, 60);
    led.drawLine(3, 62, 120, 62);
    
    led.display();
    delay(DELAYTIME);
}
