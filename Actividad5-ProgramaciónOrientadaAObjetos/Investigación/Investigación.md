# Experiencia de Aprendizaje 5: Programación Orientada a Objetos

## Introducción a los Objetos
> **Concepto:** Un objeto es una instancia de una clase que combina datos (atributos) y comportamiento (métodos).

Considera el siguiente caso de estudio:
```cpp
class Particle {
public:
    float x, y;
    void move(float dx, float dy) {
        x += dx;
        y += dy;
    }
};
```
#### ¿Qué representa la clase Particle?
La posición `x`, `y` de una partícula y su movimiento `move()`.

#### ¿Cómo interactúan sus atributos y métodos?
El método `move()` modifica la posición `x`, `y` de la partícula.

#### Prompt para ChatGPT: Explícame en detalle qué es un objeto en C++ y cómo se relaciona con una clase. Usa el ejemplo de una clase Particle con atributos `x` y `y` y un método `move`.
Later

## Explorando la Memoria

### Reflexión Guiada:
#### ¿Los atributos están almacenados de forma contigua?
Yes! Eso permite que, a partir de la ubicación en memoria de un objeto específico, todos los atributos estén "en línea" (o seguidos pues :p).

#### ¿Qué indica el tamaño del objeto sobre su estructura interna?
La cantidad y el tipo de atributos que tiene.

#### Prompt para ChatGPT: ¿Cómo se almacenan los objetos en memoria en C++? Si tengo dos instancias de Particle, ¿Cómo se relacionan sus direcciones de memoria? ¿Los atributos están contiguos?
Later

## Análisis de diferencias
```cpp
class Simple {
public:
    int a;
};

class Complex {
public:
    int a, b, c;
    void method1() {}
    void method2() {}
};
```
Un objeto de la clase `Simple` ocupa *4 bytes* de memoria (por su atributo `int a`), mientras que un objeto de la clase `Complex` ocupa *12 bytes* (pues tiene 3 atributos `int`).  
Se vale mencionar que los métodos no ocupan la misma memoria que los atributos, sino que se almacenan en el bloque dedicado a instrucciones.

### Análisis Individual
```cpp
class StaticData {
public:
    static int s;
    int a;
};

int StaticData::s = 0;

class DynamicData {
public:
    int* ptr;
    DynamicData() {
        ptr = new int[10];
    }
    ~DynamicData() {
        delete[] ptr;
    }
};
```
#### ¿Cómo afectan los datos estáticos al tamaño de la instancia?
¡No lo afectan! Resulta y acontece que los valores estáticos se guardan en *otro* espacio de memoria, entonces el tamaño de una instancia no tiene en cuenta esos datos.

#### ¿Qué diferencias hay entre datos estáticos y dinámicos en términos de memoria?
Los datos estáticos se almacenan en otra sección de memoria (`.bss` o `.data`), entonces no ocupan espacio en la `heap` o el `STACK`. Los datos dinámicos o, en este caso, el puntero que lleva a esos datos, ocupan 8 bytes porque están en la `heap`, y se necesita un puntero más grande para definir  direcciones en esta.

#### Prompt para ChatGPT: explícame cómo el uso de variables estáticas y dinámicas en una clase afecta el tamaño de sus instancias. ¿Las variables estáticas ocupan espacio en cada objeto?
Later