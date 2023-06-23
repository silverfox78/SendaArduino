# Reloj en la matriz led

Ahora uniremos los proyectos anteriores.

Especificamente la clase del reloj la usaremos para obtener la hora (HH24:MM) y la imprimiremos en la matriz led, aunque en este proceso llevaremos el uso de la matriz led tambien a una clase encapsulando la logica de impresion.

## Proyectos de referencia
- [Clase reloj](proyectos/p002_reloj_class/readme.md)       
- [Matriz Led](proyectos/p003_matriz_led/readme.md)

## Componentes
- Arduino uno
- Protoboard
- Jumpers
- Matriz led 32x8 operado con un MAX7219
- Módulo Reloj RTC DS3231
- Pila CR2032 o CR2040

## Conexiones

| MAX7219  | DS3231 | Arduino UNO |
|:--------:|:------:|------------:|
|   VCC    |  VCC   |          5V |
|   GND    |  GND   |         GND |
|          |  SDA   |          A4 |
|          |  SCL   |          A5 |
| CLK_PIN  |        |          13 |
| DATA_PIN |        |          11 |
|  CS_PIN  |        |          10 |

## Sobre el proyecto

```txt
El Sketch usa 10386 bytes (32%) del espacio de almacenamiento de programa. El máximo es 32256 bytes.
Las variables Globales usan 463 bytes (22%) de la memoria dinámica, dejando 1585 bytes para las variables locales. El máximo es 2048 bytes.
```

Mantenernos haciendo estas dos acciones y tener un tamaño del sketch en **10386 bytes (32%)** creo que es meritorio, junto con el orden en el codigo, que en este caso se limita a:

```cpp
#include <Wire.h>
#include "clock.h"
#include "mled.h"

#define BAUD_RATE 9600
#define DELAYTIME 1000

Clock clock;
MLed mled;
#define INTENSITY 2

void setup() {
  Wire.begin();
  Serial.begin(BAUD_RATE);
  mled.initialize(INTENSITY);
}

void loop() {
  mled.printText(clock.getTime(), DELAYTIME);
}
```

Si lo vemos "funcionando", tenemos algo como esto:

![Reloj en Matriz](/img/matrizled_01.jpg)

El hecho de que se escriba en forma secuencial caracter a caracter y que esto no este centrado me da algo de ansiedad, fuera de eso, no tiene nada de entretenido que solo muestra la hora asi, por ende, el siguiente proyecto sera ir agregandole algunos temas visuales y componentes adicionales.