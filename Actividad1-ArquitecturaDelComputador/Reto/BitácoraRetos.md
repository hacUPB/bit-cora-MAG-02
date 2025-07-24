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
### Considera el siguiente programa:
```asm
@var1
D = M
@var2
D = D + M
@var3
M = D
```
* **¿Qué hace este programa?**  
El programa suma los valores de 2 variables (var1 y var2) y almacena el resultado en la memoria de var3.
* **¿En qué posición de la memoria está var1, var2, y var3? ¿Por qué en esas posiciones?**  
Están en las posiciones 16, 17, y 18, respectivamente. Esto se debe a que las posiciones 0 a 15 son variables por defecto en Hack (se conocen como "virtual registers").

# Reto 9
### Considera el siguiente programa:
```c++
i = 1
sum = 0
sum = sum + i
i = i + 1
```
### La traducción a lenguaje ensamblador del programa anterior es:
```asm
// i = 1
@i
M=1
// sum = 0
@sum
M=0
// sum = sum + i
@i
D=M
@sum
M=D+M
// i = i + 1
@i
D=M+1
@i
M=D
```
* **¿Qué hace este programa?**  
Este programa crea 2 variables (*i* y *sum*), les asigna los valores 1 y 0 respectivamente, suma *i* a *sum*, y finalmente aumenta en 1 el valor de *i*.
* **¿En qué parte de la memoria RAM está la variable `i` y `sum`? ¿Por qué en esas posiciones?**  
Al igual que en el Reto 8, estarán en las posiciones 16 y 17, debido a los "virtual registers".
* **Optimiza esta parte del código para que use solo 2 instrucciones:**
```asm
// i = i + 1
@i
D=M+1
@i
M=D
```
```asm
//OPTIMIZACIÓN
// i = i + 1 ---> i += 1
@i
M=M+1
```

# Reto 10
### Las posiciones de memoria RAM de 0 a 15 tienen los nombres simbólico `R0` a `R15`. Escribe un programa en lenguaje ensamblador que guarde en `R1` la operación `2 * R0`.
```asm
@R0
D=M
D=D+M

@R1
M=D
```
Este código no resulta muy complejo. Es simplemente escribir una multiplicación en forma de suma :p

# Reto 11
### Considera el siguiente programa:
```c++
i = 1000
LOOP:
if (i == 0) goto CONT
i = i - 1
goto LOOP
CONT:
```
### La traducción a lenguaje ensamblador del programa anterior es:
```asm
// i = 1000
@1000
D=A
@i
M=D
(LOOP)
// if (i == 0) goto CONT
@i
D=M
@CONT
D;JEQ
// i = i - 1
@i
M=M-1
// goto LOOP
@LOOP
0;JMP
(CONT)
```
- **¿Qué hace este programa?**  
El programa
- **¿En qué memoria está almacenada la variable `i`? ¿En qué dirección de esa memoria?**  
En la posición 16 de la RAM.
- **¿En qué memoria y en qué dirección de memoria está almacenado el comentario //`i = 1000`?**  
Los comentarios solo existen en el archivo .asm, y no afectan ni se guardan en RAM o ROM.
- **¿Cuál es la primera instrucción del programa anterior? ¿En qué memoria y en qué dirección de memoria está almacenada esa instrucción?**  
La primera instrucción es "`@1000`". Esta instrucción se guarda en la posición 0 de la ROM.
- **¿Qué son CONT y LOOP?**  
Son *labels*. Sirven para volver fácilmente a ciertas partes específicas del código.
- **¿Cuál es la diferencia entre los símbolos `i` y `CONT`?**  
`i` es una variable, `CONT` es un label. El uno puede almacenar información, mientras que el otro simplemente representa una posición en la ROM a la que se puede saltar.

# Reto 12
### Implemente en ensamblador:
```c++
R4 = R1 + R2 + 69
```
```asm
@R1
D=M
@R2
D=D+M
@69
D=D+A

@R4
M=D
```
Facilito! Creo que ya le cogí el tiro al Assembly, por lo menos pa' la parte de sumas y tal :>

# Reto 13
