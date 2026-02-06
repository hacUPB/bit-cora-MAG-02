# Actividad 1
```c++
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 20);
}
```
- **Cuál es el resultado que se obtiene al ejecutar este programa?**  
El programa dibuja un fondo negro en el setup, y luego dibuja un círculo blanco en la posición del mouse.

# Actividad 2
### Analicemos juntos este código:

- **¿Qué fue lo que incluimos en el archivo .h?**  
Creamos un vector `vector<ofVec2f>` para almacenar `particles` y un objeto `ofColor` para `particleColor`. 
- **¿Cómo funciona la aplicación?**  
La aplicación crea círculos (o partículas) en la ubicación del mouse cuando este se mueve, hasta un límite de 100 partículas (creo). Cuando se hace click, cambia el color de las partículas a uno aleatorio.
- **¿Qué hace la función mouseMoved?**  
Detecta que se movió el mouse, crea una partícula nueva y elimina la más antigua del vector.
- **¿Qué hace la función mousePressed?**  
Detecta que se presionó el click izquierdo del Mouse y cambia el color de las partículas a uno aleatorio.
- **¿Qué hace la función setup?**  
Crea un fondo de coor negro y asigna a las partículas el color blanco por defecto.
- **¿Qué hace la función update?**  
Nada :p
- **¿Qué hace la función draw?**  
Se encarga de crear/dibujar las partículas y asignarles el color actual.

# Actividad 3
### Realiza un experimento con la aplicación anterior. Modifica alguna parte importante de su código.
Hice que la app diera epilepsia LOL

# Actividad 5
- **¿Cuál es la definición de un puntero?**  
Es una variable especial que almacena la ubicación de otra variable.
- **¿Dónde está el puntero?**  
Los punteros están en `ofApp.h`, aquí:
```c++
private:
    vector<Sphere*> spheres;
    Sphere* selectedSphere;
```
- **¿Cómo se inicializa el puntero?**  
Se utiliza un `*` luego de nombrar la variable.
- **¿Para qué se está usando el puntero?**  
Para guardar la ubicación de las distintas esferas creadas, y para recordar la dirección de la esfera seleccionada.
- **¿Qué es exactamente lo que está almacenado en el puntero?**  
La dirección en la RAM de la variable a la que apunta.

# Actividad 6
### El código anterior tiene un problema. ¿Puedes identificar cuál es? ¿Cómo lo solucionarías? Recuerda que deberías poder seleccionar una esfera y moverla con el mouse.
El problema real no fue hacer que se pudiera seleccionar cualquier esfera, sino el poder soltarla. El código simlpemente no tenía un método/una forma de soltar la esfera. La añadí así:
```c++
void ofApp::mousePressed(int x, int y, int button) {

    if (button == OF_MOUSE_BUTTON_LEFT) {
        if (selectedSphere == nullptr) {
            for (auto sphere : spheres) {
                float distance = ofDist(x, y, sphere->getX(), sphere->getY());
                if (distance < sphere->getRadius()) {

                    selectedSphere = sphere;
                    break;
                }
            }
        }
        else {
            selectedSphere = nullptr;
        }
    }
}
```

# Actividad 7
### Ahora te voy a proponer que reflexiones profundamente sobre el manejo de la memoria en un programa. Se trata de un experimento en el que tienes que analizar por qué está funcionando mal.
- **¿Qué sucede cuando presionas la tecla "c"?**  
Big problem: El código no me quiere compilar :c Lo intentaré de nuevo en casita :>
#### Realiza esta modificación a la función createObjectInStack donde claramente se está creando un objeto, pero se está creando en el heap y no en el stack, así que no te dejes confundir por el nombre de la función.
- **¿Qué sucede cuando presionas la tecla “c”?**  
Ans
- **¿Por qué ocurre esto?**  
Ans

# Actividad 8
### Construye un experimento (un programa) en el que puedas crear y dibujar objetos que se almacenan:
- **En el `heap`.**
- **En el `stack`.**
- **En memoria global.**  
Va, de una, firme, se le tiene profe 🫡
```cpp
```
- **¿Cuándo debo crear objetos en el heap y cuándo en memoria global?**  
Ans

# Actividad 9
- **¿Qué sucede cuando presionas la tecla “f”?**  
Ans
- **Analiza detalladamente esta parte del código:**  
```cpp
if(!heapObjects.empty()) {
    delete heapObjects.back();
    heapObjects.pop_back();
}
```
Ans
