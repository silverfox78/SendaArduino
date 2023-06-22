# Informacion del reloj en una clase

Esto esta basado en el proyecto anterior [aqui](../p001_reloj_set/readme.md), con la salvedad de que en este punto ya no necesitamos iniciarlizar el reloj y la idea es organizar el codigo de mejor manera.

## Proposito

Para mejorar el codigo apuntaremos a llevar organizar lo que necesitaremos del rejor en una clase y veremos como reducir la memoria usada en el proceso.

El proyecto anterios generaba esta salida:

```txt
El Sketch usa 5998 bytes (18%) del espacio de almacenamiento de programa. El máximo es 32256 bytes.
Las variables Globales usan 513 bytes (25%) de la memoria dinámica, dejando 1535 bytes para las variables locales. El máximo es 2048 bytes.
```

Osea el primer proyecto usaba **5998 bytes (18%)**, la idea es reducirlo o mantenerse cerca de ese valor.

Iniciamos por ya no usar la libreria **RTClib.h** y solo usar **Wire.h**.

## El Codigo

Organizamos nuestro proyecto de la siguiente manera:

| Archivo              | Proposito                               | Codigo                      |
|----------------------|-----------------------------------------|-----------------------------|
| p002_reloj_class.ino | Archivo principal del programa          | [ver](p002_reloj_class.ino) |
| clock.h              | Definicion de metodos de la clase       | [ver](clock.h)              |
| clock.cpp            | Clase que contendra la logica del reloj | [ver](clock.cpp)            |

## Funciones

De minuto, generaremos tres funciones publicas que usaremos mas adelante

| Funcion                   | Proposito                                                                                        |
|---------------------------|--------------------------------------------------------------------------------------------------|
| char* getTime()           | Nos entregara la hora en el formato **HH:MM**                                                    |
| char* getSecond()         | Nos entregara los segundos en el formato **SS**                                                  |
| int getSecondPercentage() | Nos entregara un numero de 0 a 100 que representa el procentaje de segundos que lleva del minuto |

## Resultado

```txt
El Sketch usa 7234 bytes (22%) del espacio de almacenamiento de programa. El máximo es 32256 bytes.
Las variables Globales usan 439 bytes (21%) de la memoria dinámica, dejando 1609 bytes para las variables locales. El máximo es 2048 bytes.
```

|Original | Actual |
|---|---|
|5998 bytes (18%)|7234 bytes (22%)|

Si bien no se logro reducir o mantener el peso en el resultado del Sketch, si se libro el uso de la libreria **RTClib.h** y se encapsulo la logica del reloj en una clase, asi que en funcion de los futuros desarrollos y la mejor lectura del codigo principal se opta por mantener este ajuste.