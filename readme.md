# Arduino

## Repo GIT

```shell
git clone https://github.com/silverfox78/SendaArduino.git
```

## Objetivo

La idea es crear un reloj simpatico que fuera de dar la hora, entrege la temperatura, humedad y sea un control bluetooth para la musica.
Tambien es posible que le sume algunos detalles adicionales.

Para este objetivo, ire avanzando poco a poco en los pasos necesarios para llegar a esto.

## Componentes iniciales

| Componente                             | Imagen referencial                                                                       | Opcion de compra                                                                                                                                                                                                                                                                                                                                    | Valor               |
|----------------------------------------|------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------|
| Arduino Uno R3 | ![Arduino Uno R3](img/arduino-uno-r3.jpg "Arduino Uno R3") | [ver](https://www.mechatronicstore.cl/arduino-uno-r3/) | $15.690|
|Protoboard |![Protoboard](img/Protoboard.jpg "Protoboard") | [ver](https://www.mechatronicstore.cl/breadboard-830-puntos-mb102/) |$ 2.490 |
| Matriz led 32x8 operado con un MAX7219 | ![Matriz led 32x8](img/MAX7219.jpg "Matriz led 32x8 operado con un MAX7219") | [ver](https://www.mechatronicstore.cl/Fmatriz-led-8x8x4-256-leds-max7219/)                                                                                                                                                                                                                                                                     | $6.890              |
| Módulo Reloj RTC DS3231                | ![Reloj DS3231](img/DS3231.png "Reloj RTC DS3231")                           | [ver](https://www.mechatronicstore.cl/modulo-reloj-rtc-ds3231/)                                                                                                                                                                                                                                                                               | $3.490              |
| Pila CR2032 o CR2040                   | ![Pila CR2032](img/CR2032.jpeg "Pila CR2032")                                | [ver](https://articulo.mercadolibre.cl/MLC-956407083-pack-tira-5-pilas-tipo-boton-duracell-dlcr-2032-_JM#is_advertising=true&position=1&search_layout=stack&type=pad&tracking_id=c3093f97-79b7-4e2a-a888-373ff0ed7da6&is_advertising=true&ad_domain=VQCATCORE_LST&ad_position=1&ad_click_id=MzUzNGE1ZWMtODYzOC00YWQ2LTgyMjAtYjY0ZTFlYzE3YjA5) | $3.325 (5 unidades) |

## Proyectos iniciales

| N | Titulo          | Descripcion                                                                                                                                                                         |
|---|-----------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1 | [Seteo del reloj](p001_reloj_set/readme.md) | Como dice el titulo, es necesario que fijemos la hora en el reloj que usaremos, pero para su uso cotidiano no sera necesario, por eso lo descomponemos en un proyecto independiente |