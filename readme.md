# Arduino

## Repo GIT

```shell
git clone https://github.com/silverfox78/SendaArduino.git
```

## Objetivo

La idea es crear un reloj simpatico que fuera de dar la hora, entrege la temperatura, humedad y sea un control bluetooth para la musica.
Tambien es posible que le sume algunos detalles adicionales.

Para este objetivo, ire avanzando poco a poco en los pasos necesarios para llegar a esto.

- [Componentes iniciales](componentes.md)
- [Componentes opcionales](opcionales.md)
- [Para el futuro](futuros.md)

## Secuencias de proyectos

| N | Titulo                                                | Descripcion                                                                                                                                                  |
|---|-------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1 | [Seteo del reloj](proyectos/p001_reloj_set/readme.md) | Es necesario que fijar la hora en el reloj que usaremos, pero para su uso cotidiano no sera necesario, por eso lo descomponemos en un proyecto independiente |
| 2 | [Clase reloj](proyectos/p002_reloj_class/readme.md)   | Organizamos el codigo buscando una mejor lectura y manejo en el futuro                                                                                       |
| 3 | [Matriz Led](proyectos/p003_reloj_leds/readme.md)     | Usamos una matriz de led (32*8) para mostrar informacion                                                                                                     |