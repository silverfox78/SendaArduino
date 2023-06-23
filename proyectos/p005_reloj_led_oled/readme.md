# Reloj en led + oled

En este proyecto sumaremos un componente, en este caso una pantalla oled SSD1306 de 0.96 pulgadas monocolor.

Fuera de ser un componente interesante, la idea principal es ver un tema en el loop del programa, asi que tomaremos el [proyecto anterior](/proyectos/p004_reloj_led/readme.md) y le sumaremos lo necesario para la pantalla oled.

## Componentes
- Arduino uno
- Protoboard
- Jumpers
- Matriz led 32x8 operado con un MAX7219
- Módulo Reloj RTC DS3231
- Pila CR2032 o CR2040
- Pantalla OLED SSD1306 de 0.96" (128 * 64)

## Conexiones

| SSD1306 | MAX7219  | DS3231 | Arduino UNO |
|:-------:|:--------:|:------:|------------:|
|   VCC   |   VCC    |  VCC   |          5V |
|   GND   |   GND    |  GND   |         GND |
|   SDA   |          |  SDA   |          A4 |
|   SCL   |          |  SCL   |          A5 |
|         | CLK_PIN  |        |          13 |
|         | DATA_PIN |        |          11 |
|         |  CS_PIN  |        |          10 |

## Primera vista

Al agregar la pantalla oled, vemos el desface en la escritura del oled (video en la imagen)

[![Reloj en Matriz y Oled](/img/reloj_led_v2.jpg)](https://youtu.be/J_re1QgfeNU)

## Sobre la pantalla oled

Usaremos las librerias:

- Adafruit_GFX.h
- Adafruit_SSD1306.h

Para la configura, necesitamos definir algunas cosas:

```c
#include <Adafruit_GFX.h>                               // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>                           // libreria para controlador SSD1306
#define ANCHO 128                                       // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64                                         // reemplaza ocurrencia de ALTO por 64
#define OLED_RESET 4                                    // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto
```

En el setup de la aplicacion deberemos iniciar la pantalla, con la **direccion 0x3C** (recordar que la pantalla como el reloj es I2C)

```c
void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);
  mled.initialize(INTENSITY);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // inicializa pantalla con direccion 0x3C
}
```

Finalmente en el loop escribiremos un texto de ejemplo:

```c
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
```

Pero el resultado no es satisfactorio, lo primero es que el tamaño del sketch casi se duplico (**20254 bytes (62%)**)

```txt
El Sketch usa 20254 bytes (62%) del espacio de almacenamiento de programa. El máximo es 32256 bytes.
Las variables Globales usan 595 bytes (29%) de la memoria dinámica, dejando 1453 bytes para las variables locales. El máximo es 2048 bytes.
````

Y visualmente debido a que la impresion en la matriz es un sub ciclo, retiene todo el funcionamiento del proyecto, por eso la pantalla oled solo se refresca cada X tiempo, asi que ahora la idea es encapsular en una clase las funcionalidades de la pantalla oled y ver como reducir el tamaño del scketch si es posible.