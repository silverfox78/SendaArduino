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
