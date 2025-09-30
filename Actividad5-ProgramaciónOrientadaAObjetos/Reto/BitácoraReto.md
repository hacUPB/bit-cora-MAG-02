# Reto
## Redacción Inicial
Mi idea general, muy poco formada, es simplemente crear una clase padre llamada "Shape" y crear múltiples subclases que representen distintas figuras geométricas dibujables con Open Frameworks (círculos, cuadrados, seguramente triángulos, y ps realmente no he consultado más).

## Clases
### Shape
* Clase padre con distintas figuras como subclases.
* **Atributos:**
    * `color`: Me gustaría que cada figura tuviera por defecto un color específico, o quizá un rango de colores similares.
    * `size`: Misma lógica de color, un tamaño específico o rango de tamaños según cada figura.
    * `key`: Algo como para guardar qué tecla representa cada figura? No sé, la verdad.
* **Métodos:**
    * `virtual draw()`: Cambiaría según cada figura (por eso es `virtual`, duh) para interactuar de forma diferente con el mouse del usuario (que ps es la manera que se me ocurre para dibujar estas cosas :p)
    * `virtual fun()`: Me gusta la idea de que cada figura pueda hacer una cosa extraña y diferente, pero aún no he pensado qué.
    * `random()`: Algo que cambie el color de la figura que está siendo dibujada a un color aleatorio. Why? No sé.

### Triangle : Shape
* **Atributos:**
* **Métodos:**
### Square : Shape
* **Atributos:**
* **Métodos:**
### Circle : Shape
* **Atributos:**
* **Métodos:**
### Star : Shape
* **Nota:** No sé si esta figura se puede dibujar siquiera LOL
* **Atributos:**
* **Métodos:**