# Tira LED

Como en el primer proyecto, iniciaremos por conectar y probar el componente, en este caso una tira led, para ser mas especifico: **Una matriz led 32x8 operado con un MAX7219**

## Componentes
- Arduino uno
- Protoboard
- Jumpers
- Matriz led 32x8 operado con un MAX7219


## Conexiones

| MAX7219  | Arduino UNO |
|----------|-------------|
| VCC      | 5V          |
| GND      | GND         |
| CLK_PIN  | 13          |
| DATA_PIN | 11          |
| CS_PIN   | 10          |


## Confuguracion en el codigo

```c
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10
#define MAX_DEVICES 4

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
```

De las posibles librerias para usar, la mas aconsejable y libiana es **MD_MAX72xx** pero nos obligara a hacer algunas cosas de manera manual, lo cual le da algo mas de entretencion al tema...