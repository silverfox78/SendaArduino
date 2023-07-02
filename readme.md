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

| N  | Titulo                                                                | Descripcion                                                                                                                                                  |
|----|-----------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1  | [Seteo del reloj](proyectos/p001_reloj_set/readme.md)                 | Es necesario que fijar la hora en el reloj que usaremos, pero para su uso cotidiano no sera necesario, por eso lo descomponemos en un proyecto independiente |
| 2  | [Clase reloj](proyectos/p002_reloj_class/readme.md)                   | Organizamos el codigo buscando una mejor lectura y manejo en el futuro                                                                                       |
| 3  | [Matriz Led](proyectos/p003_matriz_led/readme.md)                     | Usamos una matriz de led (32*8) para mostrar informacion                                                                                                     |
| 4  | [Reloj en matriz led](proyectos/p004_reloj_led/readme.md)             | Uniremos los proyectos anteriores para mostrar ahora la hora en la matriz led                                                                                |
| 5  | [Reloj en matriz led + oled](proyectos/p005_reloj_led_oled/readme.md) | Sumamos al proyecto una pantalla oled para mostrar mas informacion                                                                                           |
| 6  | [Reloj v1](proyectos/p006_reloj_v1/readme.md)                         | Se inicia la logica de muestra de informacion                                                                                                                |
| 7  | [Espacio curvo](proyectos/p007_space_demo/readme.md)                  | Demo de grafica para la pantalla OLED                                                                                                                        |
| 8  | [Funcion sin(x)](proyectos/p008_curve_sin/readme.md)                  | Test de la curva del sin(x) para la curva de las rectas                                                                                                      |
| 9  | [Libreria de Temporama](libreria/TemporamaLib/readme.md)              | Libreria destinada a contener la logica de **Temporama**                                                                                                     |
| 10 | [**T E M P O R A M A**](proyectos/Temporama/readme.md)                | Reestructuracion del proyecto original a **Temporama**                                                                                                       |

---

## Etapa 2 - Orden

- **20230701** En este punto del proyecto, si vien han habido avances, estos han sido mas bien desordenados, principalmente por la generacion de clases/librerias que no estan apropiadamente nombradas, fuera de esto la redundancia de codigo y la falta de optizacion de otros, en la busqueda de mejorar estos puntos, evalue el crear y disponder directamente de librerias para el protecto, lo cual es completamente factible, incluso el publicarlas en arduino como una libreria oficial, pero en este caso eso solo volveria mas complejo el proposito del proyecto, por ende optare por organizar todo en un nuevo espacio, renombrando las clases/librerias y optimizando sus funcionalidades, para ello creare el proyecto [**Reloj_Multifuncional**](proyectos/Temporama//readme.md). En ente mismo proceso, se generan nuevos carpetas y proyectos que contendran la logica de manera independientede las librerias.

### Actualizacion de libreria

La libreria de **Temporama** se encuentra contenida en este repositorio, pero para su uso en los proyectos debemos procurar mantener actualizada la carpeta dentro de las librerias de Arduino (esto depende de la configuracion de cada equipo), para ello en la raiz de este proyecto dejo un script que se encarga de esta accion: [Aqui](./clon_lib.sh), en el cual basicamente especificamos la ruta local de la carpeta de la libreria y la ruta de las librerias de arduino, el script se encarga de eliminar, copiar y verificar los archivos.