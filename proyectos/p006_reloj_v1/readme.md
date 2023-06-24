# Reloj - v1

Este proyecto, es un clon del anterior, solo que como en los casos previos buscamos organizar mejor el codigo y agregar alguna funcionalidad.

Si bien la idea inicial era no usar las librerias **Adafruit_GFX.h** y **Adafruit_SSD1306.h**, la opcion era usar directamente **Wire.h** para usar la pantalla OLED, el tema es que esto resulta muy engorroso, asi que simplemente asumiremos el costo de las librerias en el proyecto.

De la misma forma, le sacaremos mas partido a la libreria **MD_MAX72xx.h** para la matriz led, la idea sera crear dos clases:

- Matriz: que tendra la logica de impresion en la matriz led
- Oled: que tendra la logica de impresion en el OLED

## ¿Cual es el proposito de esto?

La idea es que en el Loop de nuestra aplicacion no useamos un delay implicito, simplemente llamemos a las estas nuevas clases y ellas en funcion de la memoria y el tiempo refresquen su informacion.

## Clase OLED

En el proyecto anterior, usamos directamente la pantalla desde el codigo principal, asi que crearemos una clase interfaz que nos permita contener sus funcionalidades (clase **LED**) y esta sera usada por la clase **OLED**.

Las funcionalidades que buscamos inicialmente para esta clase es:

- Inicializar la pantalla
- Limpiar la pantalla
- Escribir un texto, para esto necesitamos: tamaño, coordinada X e Y de la pantalla y el texto.
- Cual es la dimension de un determinado texto con cierto tamaño
- Mostrar en pantalla lo escrito

En lo que respecto a la clase **OLED**, la idea es mostrar informacion que complemente al reloj, pero esta claro que esto podria ser mucho ams dinamico y versatil.

Asi que, ¿Como lo hacemos?

Lo primero es imprimir algo en funcion del tiempo y la memoria, para eso usaremos la funcion **millis()** que nos dice cuantos milisegundos lleva en uso el dispositivo, con esto mas otras variables determinaremos que escribir o dibujar...