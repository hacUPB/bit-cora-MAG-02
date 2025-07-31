# Actividad 1
**En el capítulo 4 del libro “The Elements of Computing Systems” que puedes encontrar [aquí](https://www.nand2tetris.org/_files/ugd/44046b_7ef1c00a714c46768f08c459a6cab45a.pdf), vas a repasar de nuevo cómo se realizan las operaciones de entrada y salida en la plataforma de cómputo que estamos estudiando, es decir, la plataforma Hack y la CPU Hack. También puedes ver [este video](https://youtu.be/gTOFd80QfBU?si=6FLpT907cx1Q_NDB), si quieres, donde te explican el concepto. En la sección 4.2.5. vas a encontrar el concepto de entrada-salida mapeada a memoria o memory maped I/O. Analiza lo siguiente:**

- **¿Qué es la entrada-salida mapeada a memoria?**  
Son entradas y salidas que ya tienen una posición específica determinada en la memoria *RAM* del PC. La pantalla es una salida mapeada entre las posiciones `16384` y `24575`, y el teclado es una entrada mapeada al último valor de la *RAM* (que es el `24576` en el emulador de *Nand2Tetris*).
- **¿Cómo se implementa en la plataforma Hack?**  
Podemos interactuar directamente con las posiciones específicas (como por ejemplo, usando `@24576`) o llamar las constantes simbólicas asociadas a esas posiciones (`@KBD` y `@SCREEN`).  
- **Inventa un programa que haga uso de la entrada-salida mapeada a memoria.**  
Ok va, on it.
```asm
(LOOP)
    @69
    D=A
    @KBD
    D=M-D

    @DRAW
    D;JEQ
    @LOOP
    0;JMP

(DRAW)
    @SCREEN
    D=A
    @j
    D=D+M
    A=D
    M=-1

    @j
    M=M+1

    @LOOP
    0;JMP
```
Este es un programa bastante simple, pero cumple con el propósito :p

- **Investiga el funcionamiento del programa con el simulador.**  
El programa está en un loop constante esperando que se presione la tecla "`E`" (específicamente en mayúscula, sea usando Shift o Caps Lock) y, mientras esta es presionada, dibuja una línea horizontal en la pantalla.  
Cuando el código se ejecuta a velocidad rápida es muy difícil detenerlo antes de que llene una buena porción de la pantalla.

# Actividad 2
**Vas a revisar de nuevo el reto 20 de la unidad anterior. Asegúrate de entenderlo, simularlo y experimentar con él antes de continuar con el siguiente reto.**  
Ejercicio revisado en clase.

# Actividad 3
**Vas a implementar y simular una modificación al reto 20 de la unidad anterior. Si se presiona la letra “d” muestras la imagen que diseñaste en el reto 18. Si no se presiona ninguna tecla, borrarás la imagen.**  
Realizado en `actividad3.asm`

# Actividad 4
**Ahora realizarás una nueva variación al programa de la actividad anterior. Si se presiona la letra “`d`” muestras la imagen que diseñaste en el reto 18. Solo si se presiona la letra “`e`” borrarás la imagen que se muestra en pantalla.**  
Realizado en `actividad4.asm`