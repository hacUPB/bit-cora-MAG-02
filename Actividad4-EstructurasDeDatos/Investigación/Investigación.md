# Experiencia de Aprendizaje : Estructuras de Datos

## Actividad 1:
#### 1. **Entiende la aplicación:** comienza explorando detenidamente cómo funciona el programa. Usa un un modelo del lenguaje como ChatGPT y el depurador para que verifiques las explicaciones que te propone ChatGPT. Puedes escribir el prompt: *"Se requiere entender de manera muy detallada el siguiente programa escrito en C++ y el OpenFrameworks"*. Luego le das el código. Ve preguntando lo que no entiendas. Recuerda ir usando al mismo tiempo el depurador de visual studio.
#### 2. **Realiza evaluaciones formativas:** Dile a ChatGPT que te genere preguntas para verificar si entiendes cómo funciona el programa. Trata de verificar tus hipótesis usando el depurador y luego con las conclusiones del experimento responde la pregunta de ChatGPT. Continúa con este proceso hasta que estés seguro de que entiendes cómo funciona el programa.

**Preguntas de ChatGPT:**  
📌 Preguntas básicas

1. ¿Qué representa cada Node en el programa y qué información guarda?
2. ¿Cuál es la diferencia entre head y tail en la clase LinkedList?
3. ¿Qué efecto tiene llamar a snake.clear() en tiempo de ejecución?

📌 Preguntas sobre el flujo del programa

4. ¿Qué ocurre en setup() respecto a la creación de nodos de la serpiente? ¿Cuántos nodos en total se crean al inicio?
5. ¿Qué pasa cada vez que se llama a update() con las coordenadas del mouse? Explica cómo se propagan las posiciones a través de la lista.
6. ¿Por qué en draw() se vuelve a llamar a ofBackground(220) si ya se había establecido un fondo en setup()?

📌 Preguntas sobre punteros y memoria

7. ¿Por qué LinkedList necesita un destructor (~LinkedList) que llame a clear()?
8. En el método addNode(x, y), ¿qué diferencia hay entre el caso if (tail != nullptr) y el else? ¿Cuándo se ejecuta cada uno?
9. ¿Qué pasaría si no se usara delete en clear() y solo se pusiera head = tail = nullptr?

📌 Pregunta de razonamiento

10. Si quisiera que la serpiente mantuviera siempre exactamente 10 segmentos, aunque se llame clear() y luego se empiece a mover el mouse, ¿qué cambios harías en el código para lograrlo?

**Mis respuestas:**  
1. Un Node es una esfera individual. Cada uno guarda la posición de la esfera y cuál esfera es la siguiente en la LinkedList.
2. Head es el primer nodo de la serpiente y Tail es el último. Al momento de crear la lista, habrá 1 nodo que sea Head y Tail, y cada vez que se añada un nodo nuevo, este se convertirá en la nueva Tail.
3. Limpia todos los nodos, es decir, borra la serpiente.
4. En setup se crean 10 nodos, y se añaden al nodo ya existente de cuando se utilizó el constructor de LinkedList.
5. Cuando se llama update() el nodo Head guarda su posición actual, se mueve a las coordenadas del mouse, y le informa al siguiente nodo que debe moverse. Este siguiente nodo guarda su posición, toma la posición anterior de Head, y también informa al siguiente nodo, y así sucesivamente.
6. Es una redundancia.
7. Porque, si no existiera el destructor directamente, los Nodos quedarían almacenados en la memoria indefinidamente.
8. Si Tail != nullptr, eso quiere decir que existe un nodo Tail, y por lo tanto solo debe añadir el nuevo nodo creado a la cola y reemplazar Tail. Si Tail == nullptr, significa que no existe una serpiente aún, y por lo tanto le asigna al nodo creado ser Head y Tail al mismo tiempo, para que todo funcione correctamente cuando se añadan otros nodos.
9. No se borrarían los Nodos de la memoria, sino que simplemente se des-enlazarían por decir así de Head y Tail. Es como decir que se limpió la casa por esconder la basura o ignorarla.
10. Podría estar constantemente verificando la variable "size". Si es menor que 10, llamo addNode, y si es mayor que 10, llamo el destructor de nodo (aunque no está programado aún).

**Retroalimentación de ChatGPT:**  
📌 Respuestas básicas

1. ✅ Correctísimo. El Node representa cada segmento (esfera), guarda su posición (x, y) y un puntero al siguiente nodo en la lista.
2. ✅ Exacto. Muy bien explicado el caso inicial de que head = tail cuando hay un solo nodo.
3. ✅ Sí: clear() borra todos los nodos de la memoria y la serpiente queda vacía.

📌 Flujo del programa

4. ✅ Muy bien: al inicio ya hay 1 nodo creado en el constructor de LinkedList. Luego en setup() se añaden 10 más, en total 11 nodos.
5. 🔍 Casi perfecto, pero un pequeño matiz: el head no “guarda” su posición actual antes de moverse. En realidad, la posición del mouse se usa como prevX, prevY. Luego se recorre la lista y cada nodo adopta la posición del “previo”. Es decir:
    - El primer nodo toma la posición del mouse directamente.
    - El segundo nodo toma la posición anterior del primero.
    - El tercero la del segundo, y así sucesivamente.
    Tu explicación iba bien, pero la cabeza no se mueve a su propia posición previa, sino directamente al mouse.
6. ✅ Correcto: es redundancia. El fondo blanco puesto en setup() ni se llega a ver, porque draw() lo sobrescribe en cada frame con gris.

📌 Punteros y memoria

7. ✅ Exacto. El destructor es necesario porque si no liberas memoria de cada Node, cada vez que corras el programa (o borres y crees nodos) vas acumulando “fugas de memoria”.
8. ✅ Correctísimo. Muy bien lo de que el caso else ocurre solo cuando la lista está vacía (ejemplo: tras clear()).
9. ✅ Muy bien la analogía. Sería como “perder la referencia” a la basura, pero sigue ocupando memoria. Eso sería un memory leak.

📌 Razonamiento

10. ✅ Tu idea de controlar size es muy buena. Lo típico sería:
    - Al inicio crear exactamente 10 nodos.
    - En update(), si size < 10, agregar nodos.
    - Si size > 10, eliminar desde la cola hasta quedar en 10.  
    Y sí, para acortar la lista haría falta implementar un método tipo removeLastNode() que haga delete al último nodo y actualice tail.

#### 3. ¿Qué es una lista enlazada y en qué se diferencia de un arreglo en cuanto a la forma en que los elementos están almacenados en la memoria?
Una lista enlazada en un grupo de nodos que guardan información y un puntero al siguiente en la lista. Las listas enlazadas pueden estar almacenadas en lugares distintos de memoria, a diferencia de un array normal que está almacenado en un solo bloque.
#### 4. Al observar el código de una lista enlazada en C++, ¿Cómo crees que se vinculan los nodos entre sí? ¿Qué estructura se utiliza para lograr esta conexión?  
Es todo a base de punteros `Nodo*`. Un nodo tiene un atributo `next` que apunta al siguiente nodo en la LinkedList.
#### 5. ¿Cómo se gestiona la memoria en una lista enlazada? Investiga cómo se crea y se destruye un nodo en memoria utilizando el operador new y delete en C++.  
Cuando se crea un nodo con `new`, se le asigna un espacio libre en la `Heap` y retorna un puntero a este espacio. Al momento de borrar un nodo, se libera el espacio en el que estaba y se destruye con `delete`.
#### 6. Considerando la estructura de una lista enlazada, ¿qué ventajas ofrece en comparación con un arreglo cuando se trata de insertar o eliminar elementos en posiciones intermedias?  
En una lista enlazada es más fácil agregar un valor "metido" entre otros porque solo es necesario cambiar 1 puntero (el del Nodo anterior) para que apunte al nuevo Nodo. Eso sí, es necesario recorrer la lista hasta llegar al nodo específio en el que se va a insertar el nuevo nodo. La ventaja es que no hay que mover todos los otros índices ni nada por el estilo.
#### 7. En el código presentado, ¿Cómo se asegura que no haya fugas de memoria? ¿Qué papel juega el destructor en la clase LinkedList?  

#### 8. ¿Qué sucede en la memoria cuando se invoca el método clear() en una lista enlazada? Explica paso a paso cómo se liberan los recursos.  
Ans
#### 9. Explica cómo cambia la estructura en memoria de una lista enlazada al agregar un nuevo nodo al final de la lista. ¿Cómo afecta esto al rendimiento de la lista enlazada?  
Ans
#### 10. Analiza una situación en la que utilizar una lista enlazada sería más ventajoso que utilizar un arreglo. Justifica tu respuesta considerando la gestión de memoria y las operaciones de inserción y eliminación.  
Ans
#### 11. Después de estudiar el manejo de memoria en listas enlazadas, ¿Cómo aplicarías este conocimiento para diseñar una estructura de datos personalizada para una aplicación creativa? ¿Qué aspectos considerarías para asegurar la eficiencia y evitar fugas de memoria?  
Ans
#### 12. Reflexiona sobre las diferencias en la gestión de memoria entre C++ y un lenguaje con recolección de basura automática como C#. ¿Qué ventajas y desafíos encuentras en la gestión explícita de memoria en C++ al trabajar con estructuras de datos?  
Ans
#### 13. Imagina que estás optimizando una pieza de arte generativo que usa listas enlazadas para representar elementos en movimiento. ¿Qué consideraciones tomarías en cuenta para garantizar que la gestión de la memoria sea eficiente y que no ocurran fugas de memoria?  
Ans
#### 14. **Pruebas:** pregunta a ChatGPT cómo podrías probar las partes del programa y el programa completo. Luego realiza las pruebas y verifica si los resultados coinciden con tus expectativas.**  
Ans

## Actividad 2:
#### 1. **Entendiendo la aplicación**: comienza explorando detenidamente cómo funciona el programa. Usa un un modelo del lenguaje como ChatGPT y el depurador para que verifiques las explicaciones que te propone ChatGPT. Puedes escribir el prompt: quiere entender de manera muy detallada el siguiente programa escrito en C++ y el openframeworks. Luego le das el código. Ve preguntando lo que no entiendas. recuerda ir usando al mismo tiempo el depurador de visual studio.
#### 2. **Realiza evaluaciones formativas**. Dile a ChatGPT que te genere preguntas para verificar si entiendes cómo funciona el programa. Trata de verificar tus hipótesis usando el depurador y luego con las conclusiones del experimento responde la pregunta de ChatGPT. Continúa con este proceso hasta que estés seguro de que entiendes cómo funciona el programa.
#### 3. **Pruebas:** pregunta a ChatGPT cómo podrías probar las partes del programa y el programa completo. Luego realiza las pruebas y verifica si los resultados coinciden con tus expectativas.

### Preguntas de reflexión para el stack:
#### 1. ¿Cómo se gestiona la memoria en una implementación manual de un stack en C++? Reflexiona sobre cómo el uso de new y delete en la creación y destrucción de nodos afecta el rendimiento y la seguridad de tu programa.
#### 2. ¿Por qué es importante liberar la memoria cuando se desapila un nodo en un stack? Considera las consecuencias de no liberar memoria en términos de fugas de memoria y cómo esto puede impactar aplicaciones de largo tiempo de ejecución.
#### 3. ¿Qué diferencias existen entre usar un stack de la STL (std::stack) y crear un stack manualmente? Explora cómo la abstracción que proporciona la STL puede simplificar la implementación, pero también cómo una implementación manual ofrece mayor control sobre la gestión de recursos.
#### 4. ¿Cómo afecta la estructura de un stack al orden de acceso y eliminación de elementos? Analiza cómo la naturaleza LIFO (Last In, First Out) del stack influye en los tipos de problemas que esta estructura de datos puede resolver eficientemente.
#### 5. ¿Cómo podrías modificar el stack para almacenar tipos de datos más complejos (e.g., objetos con múltiples atributos) sin causar problemas de memoria? Reflexiona sobre cómo gestionar adecuadamente la memoria para objetos más complejos y cómo esto afectaría tu implementación actual.
