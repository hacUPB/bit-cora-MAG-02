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
Respuesta de ChatGPT:

>**¿Clase vs objeto?**
>
>- **Clase = plantilla / blueprint / tipo.** Define qué datos (atributos) y qué comportamiento (métodos) tendrá un objeto.
>
>- **Objeto = instancia de esa clase:** es un bloque concreto de memoria que contiene los datos definidos por la clase y puede ejecutar sus métodos.
En términos simples: la clase es la receta; el objeto es el pastel que hiciste con esa receta.

## Explorando la Memoria

### Reflexión Guiada:
#### ¿Los atributos están almacenados de forma contigua?
Yes! Eso permite que, a partir de la ubicación en memoria de un objeto específico, todos los atributos estén "en línea" (o seguidos pues :p).

#### ¿Qué indica el tamaño del objeto sobre su estructura interna?
La cantidad y el tipo de atributos que tiene.

#### Prompt para ChatGPT: ¿Cómo se almacenan los objetos en memoria en C++? Si tengo dos instancias de Particle, ¿Cómo se relacionan sus direcciones de memoria? ¿Los atributos están contiguos?
Se le preguntó al profesor :p Los atributos y objetos están contiguos. La dirección/ubicación de un objeto es simplemente el lugar donde empiezan a listarse sus atributos y, cuando estos se terminan, empieza el otro objeto y sus atributos.

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
Se le preguntó al profesor :p Las variables estáticas no ocupan espacio en cada objeto, sino que se van a la sección `.bss` o `.data`, y se referencian desde allá por cada objeto.

## Reflexión
Documenta en tu bitácora de aprendizaje:

#### ¿Qué es un objeto desde la perspectiva de la memoria?
Un objeto es básicamente un conjunto de atributos (en términos de memoria), ya que el objeto en sí simplemente determina dónde empieza la lista de sus atributos en memoria, y ocupa el espacio de sus atributos.

#### ¿Cómo influyen los atributos y métodos en el tamaño y estructura del objeto?
Los atributos conforman todo el tamaño de un objeto, y están ubicados en orden en la memoria (empezando en la ubicación del objeto). Los métodos no ocupan espacio en una instancia de una clase, ya que estos se almacenan en un espacio diferente de la memoria.

#### Conclusión: resumir los hallazgos y cómo esto impacta el diseño de clases.
Trabajar POO en C++ es gracioso, aún no entiendo bien las estructuras pero ahí vamos wooo. En fin, más que todo diría que el mayor hallazgo es el funcionamiento de la memoria en C++, y cómo los atributos de cada objeto son empaquetados en la memoria empezando en la ubicación del objeto. También me parece muy increíble que los atributos estáticos no ocupan memoria por cada instancia y que los punteros de la `heap` ocupan más espacio por estar en un sistema de 64 bits. Creo que eso último es algo muy simple pero me parece muy chévere :p

## Análisis de la estructura de una clase

- **Datos:** los atributos se almacenan en el stack o heap, según cómo se instancien.
- **Métodos:** el código de los métodos reside en la sección de código (texto) del programa.
- **Vtables:** estructuras usadas para implementar métodos virtuales.

**Prompt para ChatGPT:** ¿Dónde se almacenan los datos y métodos de una clase en C++ en la memoria? Explica el concepto de vtable y cómo se relaciona con los métodos virtuales. 

> ℹ️ Prueba rápida de Callouts  
>
> A ver cómo se ve esta carajada :p

Respuesta de ChatGPT:
> Cuando creas un objeto de una clase (por ejemplo, `Particle p(1,2);`), lo que se guarda en memoria es solo el **conjunto de atributos (datos miembro)**.  
> * Los **métodos** no viven dentro del objeto. Están compilados como funciones normales en la sección de **código** (text segment) del programa.  
>
> Cuando escribes `p.move(1,2)`, lo que realmente pasa es que el compilador traduce eso a una llamada de función donde `p` se pasa como puntero oculto (`this`).
Así que el objeto `no almacena el código del método`, solo sus datos. El código está en otra parte (segmento de código).  
>
> **¿Qué pasa con los métodos virtuales?**  
> Aquí aparece el concepto de **vtable** *(virtual table).*
> * Una *vtable* es una tabla (arreglo de punteros a funciones) que el compilador genera automáticamente para clases con métodos virtuales.
> * Cada **clase con virtuales** tiene su propia vtable.
> * Cada **objeto de esa clase** guarda un puntero oculto a la vtable, llamado **vptr** (virtual pointer).