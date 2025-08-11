# Reto 1
### Escribe un programa en lenguaje ensamblador que sume los primeros 100 números naturales

```c++
int i = 1;
int sum = 0;
While (i <= 100){
   sum += i;
   i++;
}
```

**Código en *Assembly*:**  
```asm
(LOOP)    
    @100
    D=A
    @i
    D=D-M
    @END
    D;JLT

    @i
    D=M
    @sum
    M=D+M

    @i
    M=M+1

    @LOOP
    0;JMP

(END)
    @END
    0;JMP
```

- **¿Cómo están implementadas las variables `i` y `sum`?**  
En el código de *Assembly* se ven como `@i` y `@sum`. Internamente, estas son simplemente `@16` y `@17` respectivamente, que son las posiciones de memoria en dónde residen ambas variables.

- **¿En qué direcciones de memoria están estas variables?**  
`@i` está en `@16` y `@sum` está en `@17`.

- **¿Cómo está implementado el ciclo `while`?**  
El `while` es simplemente la comparación que se realiza al inicio del `(LOOP)`. Si `i` es mayor que `100`, simplemente no entra al ciclo y salta a `(END)`. Eso representa un `while`, porque sale del ciclo justo cuando se cumple la condición.

- **¿Cómo se implementa la variable `i`?**  
Simplemente se llama `@i`, y el mismo *Assembly* se encarga de recordar que ahora `@i` se refiere a la posición de memoria `@16`.

- **¿En qué parte de la memoria se almacena la variable `i`?**  
En la posición `@16`.

- **Después de todo lo que has hecho, ¿Qué es entonces una variable?**  
Es simplemente un símbolo que representa una posición en la memoria *RAM*. Con este símbolo es más fácil referenciar posiciones específicas que guardan información que se necesitará más tarde.

- **¿Qué es la dirección de una variable?**  
La posición de memoria *RAM* que ocupa. `@16` para `@i` y `@17` para `@sum`.

- **¿Qué es el contenido de una variable?**  
Puede ser cualquier número entero entre -32767 y 32768.

# Reto 2
### Transforma el programa en alto nivel anterior para que utilice un ciclo `for` en vez de un ciclo `while`.

En realidad no hay diferenciación entre el ciclo `for` y el ciclo `while` en Assembly. Se podría interpretar/leer de manera diferente para decir que se está ejecutando un `for` en vez de un while o viceversa, pero en realidad no existe una diferencia explícita.

# Reto 3
### Escribe un programa en lenguaje ensamblador que implemente el programa anterior.

# Reto 5
### Traduce este programa a lenguaje ensamblador:
```c++
int var = 10;
int *punt;
punt = &var;
*punt = 20;
```

# Reto 7
### Traduce este programa a lenguaje ensamblador:
```c++
int var = 10;
int bis = 5;
int *p_var;
p_var = &var;
bis = *p_var;
```

# Reto 8
### Vas a parar un momento y tratarás de recodar de memoria lo siguiente. Luego verifica con un compañero o con el profesor.
- **¿Qué hace esto `int *pvar;`?**
- **¿Qué hace esto `pvar = var;`?**
- **¿Qué hace esto `var2 = *pvar`?**
- **¿Qué hace esto `pvar = &var3`?**

# Reto 9
### Considera que el punto de entrada del siguiente programa es la función main, es decir, el programa inicia llamando la función main. Vas a proponer una posible traducción a lenguaje ensamblador de la función suma, cómo llamar a suma y cómo regresar a std::cout << "El valor de c es: " << c << std::endl; una vez suma termine.
```c++
#include <iostream>

int suma(int a, int b) {
   int var = a + b;
   return var;
}


int main() {
   int c = suma(6, 9);
   std::cout << "El valor de c es: " << c << std::endl;
   return 0;
}
```
