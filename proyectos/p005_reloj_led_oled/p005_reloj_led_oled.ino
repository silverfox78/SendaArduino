#include <Wire.h>
#include "clock.h"
#include "mled.h"

#include <Adafruit_GFX.h>                               // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>                           // libreria para controlador SSD1306
#define ANCHO 128                                       // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64                                         // reemplaza ocurrencia de ALTO por 64
#define OLED_RESET 4                                    // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto

#define BAUD_RATE 9600
#define DELAYTIME 500

Clock clock;
MLed mled;
#define INTENSITY 2

void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);
  mled.initialize(INTENSITY);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // inicializa pantalla con direccion 0x3C
}

void loop() {
  oled.clearDisplay();              // limpia pantalla
  oled.setTextColor(WHITE);         // establece color al unico disponible (pantalla monocromo)
  oled.setCursor(0, 0);             // ubica cursor en inicio de coordenadas 0,0
  oled.setTextSize(1);              // establece tamano de texto en 1
  oled.print("Hola, han pasado:");  // escribe en pantalla el texto
  oled.setCursor(10, 30);           // ubica cursor en coordenas 10,30
  oled.setTextSize(2);              // establece tamano de texto en 2
  oled.print(millis() / 1000);      // escribe valor de millis() dividido por 1000
  oled.print(" seg.");              // escribe texto
  oled.display();                   // muestra en pantalla todo lo establecido anteriormente

  mled.printText(clock.getTime(), DELAYTIME);
}
