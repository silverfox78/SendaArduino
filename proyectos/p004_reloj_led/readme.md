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
