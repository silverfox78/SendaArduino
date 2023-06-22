# Seteo del reloj

El proposito de este proyecto es simple, es el meramente setear la hora del equipo local en el modulo **DS3231**.

## Componentes
- Arduino uno
- Protoboard
- Jumpers
- Módulo Reloj RTC DS3231
- Pila CR2032 o CR2040

## Conexiones

| DS3231 | Arduino UNO |
|--------|-------------|
| VCC    | 5V          |
| GND    | GND         |
| SDA    | A4          |
| SCL    | A5          |

Considerar que este un modulo I2C y se usara una direccion para su uso, en este caso:

```c
#define DS3231_ADDRESS 0x68
```