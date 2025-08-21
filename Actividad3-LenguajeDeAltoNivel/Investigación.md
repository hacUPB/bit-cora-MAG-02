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

# Actividad 5
- **¿Cuál es la definición de un puntero?**  
Es una variable especial que almacena la ubicación de otra variable.
- **¿Dónde está el puntero?**  
Uy profe la verdad npi cómo así que dónde está?
- **¿Cómo se inicializa el puntero?**  
Se utiliza un `*` luego de nombrar la variable.
- **¿Para qué se está usando el puntero?**
- **¿Qué es exactamente lo que está almacenado en el puntero?**  
La dirección en la RAM de la variable a la que apunta.