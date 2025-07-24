# Retos 1 a 7
## Reto 1
**Carga en D el valor 1978**  
Facilito.

## Reto 2
**Guarda en la posición 100 de la RAM el número 69**  
Este toca en 2 pasos, pero también es facilito.

## Reto 3
**Guarda en la posición 200 de la RAM el contenido de la posición 24 de la RAM**  
Acá se me generó una duda: No sabía cómo llamar un dato cualquiera ubicado en la posición 24.
Luego de asignar un valor a esta posición, solo había que "pasar" el valor *M* de **@24** a *D*, y desde *D* pude agregarlo a la *M* de **@200**.  
También confirmé que el código funcionara si cambio el valor de **@24** directamente.

## Reto 4
**Lee lo que hay en la posición 100 de la RAM, resta 15 y guarda el resultado en la posición 100 de la RAM**  
Este no estuvo facilito :c  
Aunque en realidad fue solo cuestión de verificar las operaciones posibles. Intenté hacer simplemente *D-A*, pero lógicamente tenía que hacer *D=D-A*

## Reto 5
**Suma el contenido de la posición 0 de la RAM, el contenido de la posición 1 de la RAM y con la constante 69. Guarda el resultado en la posición 2 de la RAM**  
Bueno, este tiene pinta de que empieza a ser más larguito, pero piloteable.  
No fue tan difícil, era solo cuestión de organizar bien las *D*, *A*, y *M* en las operaciones :P También decidí ponerles el mismo valor a **@0** y **@1** porque se puede simplemente sumar 1 a M entonces ajá, un poquito de pereza xd

## Reto 6
**Si el valor almacenado en D es igual a 0 salta a la posición 100 de la ROM**  
Facilito también! Solo tocó consultar las instrucciones de Branching :p

## Reto 7
**Si el valor almacenado en la posición 100 de la RAM es menor a 100 salta a la posición 20 de la ROM**  
Este debería ser fácil, creo yo.  
Efectivamente, sólo había que leer la Lecture 4 porque tienen el ejemplo clarito ahí :p (Pg. 62). Algo que me confunde es ¿por qué *D* aparece como 65490 cuando le resto 100? Estoy asumiendo que es simplemente la manera de manejar negativos de *Assembly*.

# Reto 8
