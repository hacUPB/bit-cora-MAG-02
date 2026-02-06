# Reto

## Propuesta
Quiero hacer un código similar al ejemplo #3, pero esta vez quiero dar una impresión de que se está haciendo un hueco en el plano en vez de levantar el círculo al rededor del mouse.  
Eso cubriría principalmente el vertex shader, y para el fragment shader me gustaría también oscurecer los fragmentos en ese círculo para "vender" más la ilusión de profundidad.

## Proceso
Para dar la ilusión de profundidad en vez de relieve se puede simplemente cambiar la suma del vector de dirección a la posición del vértice por una resta:
```glsl
// add the direction vector to the vertex position.
pos.x -= dir.x;
pos.y -= dir.y;
```
(El comentario original dice sumar, pero nosotros restamos malévolamente c:< )  
La cosa es que más que verse como un círculo, parece un chuzón en la malla. Me gustaría que fuera un círculo :p

Llegué a este resultado que me gusta un poquito más:
```glsl
// subtract the direction vector to the vertex position.
pos.x -= dir.x;
pos.y -= dir.y;

// push them outwards a little bit
pos.x += dir.x/3;
pos.y += dir.y/3;
```
Y creo que puedo seguir con mi propósito usando el *fragment shader*. Pero primero, cambié el `plane.drawWireframe()` por simplemente `plane.draw()` para poder apreciar mejor el color del plano (y los cambios que voy a hacer).

## Resultado
Bueno, pasó un tiempo de full motivación y cero bitácora, pero el resultado quedó muy muy bacano wooooo  
Para poder hacer que el *fragment shader* afectara los fragmentos según su posición, tenía que enviarle desde el *vertex shader* la posición interpolada de esos fragments (que enredo, x Dios). Eso lo logré haciendo estos cambios a ambos *shaders*:  

`vertex.shader`:
```glsl
// Al inicio del código:
out vec2 vPosition;

// Al final del código:
	vPosition = pos.xy;
```
Estas líneas declaran que el *vertex shader* va a enviar `vec2 vPosition` al *fragment shader*, y luego le asignan el valor de la posición final del vértice específico. Creo que ya el *fragment shader* es el que hace la interpolación de la posición.  

`fragment.shader`:
```glsl
// Al inicio del código:
in vec2 vPosition;

// Y luego puedo usar la misma lógica del *vertex shader* para asignar el color:
uniform float mouseRange;
uniform vec2 mousePos;

// copy position so we can work with it.
	vec2 pos = vPosition;
    
	// direction vector from mouse position to vertex position.
	vec2 dir = pos.xy - mousePos;
    
	// distance between the mouse position and vertex position.
	float dist =  sqrt(dir.x * dir.x + dir.y * dir.y);
    
	// check vertex is within mouse range.
	if(dist > 0.0 && dist < mouseRange) {
		
		// normalise distance between 0 and 1.
		float distNorm = dist / mouseRange;
        
		// flip it so the closer we are the greater the repulsion.
		distNorm = 1.0 - distNorm;

		outputColor = mouseColor - sin(distNorm/2);
	}
	else{
		outputColor = mouseColor;
	}
```
Ya desde el *fragment shader* es solo reutilizar la lógica que ya teníamos del *vertex shader* y voilá, se logró :>  
Ah, btw, utilicé `sin(distNorm/2)` como el valor a restar del color del fragmento porque así no se llega a ser completamente transparente y se siente un poquito más "*smooth*" (según yo :p)

Ah! Y también le añadí que el `draw()` cambiara entre `plane.draw()` y `plane.drawWireframe()` según si se está presionando espacio o no (usando uno de los retos anteriores) :> 

# Evidencias de los Resultados de Aprendizaje

## Código de la aplicación:
`ofApp.h` (Porque añadí la variable `wires` para la funcionalidad con el teclado):
```cpp
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:

	// Me tocó añadir esto pa' que funcionara con teclado JAJAJAJAJA
	bool wires = false;

	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofShader shader;
	ofPlanePrimitive plane;
};
```

`ofApp.cpp`:
```cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	if(ofIsGLProgrammableRenderer()){
		shader.load("shadersGL3/shader");
	}else{
		shader.load("shadersGL2/shader");
	}

	int planeWidth = ofGetWidth();
	int planeHeight = ofGetHeight();
	int planeGridSize = 20;
	int planeColums = planeWidth / planeGridSize;
	int planeRows = planeHeight / planeGridSize;
	
	plane.set(planeWidth, planeHeight, planeColums, planeRows, OF_PRIMITIVE_TRIANGLES);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	shader.begin();
	
	// center screen.
	float cx = ofGetWidth() / 2.0;
	float cy = ofGetHeight() / 2.0;
	
	// the plane is being position in the middle of the screen,
	// so we have to apply the same offset to the mouse coordinates before passing into the shader.
	float mx = mouseX - cx;
	float my = mouseY - cy;
	
	// we can pass in a single value into the shader by using the setUniform1 function.
	// if you want to pass in a float value, use setUniform1f.
	// if you want to pass in a integer value, use setUniform1i.
	shader.setUniform1f("mouseRange", 150);
	
	// we can pass in two values into the shader at the same time by using the setUniform2 function.
	// inside the shader these two values are set inside a vec2 object.
	shader.setUniform2f("mousePos", mx, my);
	
	// color changes from magenta to blue when moving the mouse from left to right.
	float percentX = mouseX / (float)ofGetWidth();
	percentX = ofClamp(percentX, 0, 1);
	ofFloatColor colorLeft = ofColor::magenta;
	ofFloatColor colorRight = ofColor::blue;
	ofFloatColor colorMix = colorLeft.getLerped(colorRight, percentX);
	
	// create a float array with the color values.
	float mouseColor[4] = {colorMix.r, colorMix.g, colorMix.b, colorMix.a};
	
	// we can pass in four values into the shader at the same time as a float array.
	// we do this by passing a pointer reference to the first element in the array.
	// inside the shader these four values are set inside a vec4 object.
	shader.setUniform4fv("mouseColor", mouseColor);
	
	ofTranslate(cx, cy);

	// Voy a añadir una mini-funcionalidad de que, si presiono espacio, se dibuja el Wireframe
	// Y pa' eso voy a desenterrar los retos anteriores jejeje
	if (wires) {
		plane.drawWireframe();
	} else {
		plane.draw();
	}

	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'w':
		ofLog() << "Tecla detectada: " << key;
		if (wires) {
			wires = false; // Apaga el Wireframe
			break;
		} else {
			wires = true; // Dibuja el Wireframe
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
```

`shader.vert`:
```glsl
OF_GLSL_SHADER_HEADER

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
in vec4 position;

uniform float mouseRange;
uniform vec2 mousePos;
uniform vec4 mouseColor;

// Necesario pa' que el fragment shader funcione como quiero:
out vec2 vPosition;

void main()
{
    // copy position so we can work with it.
    vec4 pos = position;
    
    // direction vector from mouse position to vertex position.
	vec2 dir = pos.xy - mousePos;
    
    // distance between the mouse position and vertex position.
	float dist =  sqrt(dir.x * dir.x + dir.y * dir.y);
    
    // check vertex is within mouse range.
	if(dist > 0.0 && dist < mouseRange) {
		
		// normalise distance between 0 and 1.
		float distNorm = dist / mouseRange;
        
		// flip it so the closer we are the greater the repulsion.
		distNorm = 1.0 - distNorm;
		
        // make the direction vector magnitude fade out the further it gets from mouse position.
        dir *= distNorm;

		//AQUÍ EMPIEZA MI ESQUIZOFRENIA

		// subtract the direction vector to the vertex position.
		pos.x -= dir.x;
		pos.y -= dir.y;

		// push them outwards a little bit
		pos.x += dir.x/3;
		pos.y += dir.y/3;
	}

	// Enviar al fragment shader
	vPosition = pos.xy;

	// finally set the pos to be that actual position rendered
	gl_Position = modelViewProjectionMatrix * pos;
}
```

`shader.frag`:
```glsl
OF_GLSL_SHADER_HEADER

out vec4 outputColor;

uniform vec4 mouseColor;

// Estos son los uniforms que necesito pa' los cambios:
in vec2 vPosition;
uniform float mouseRange;
uniform vec2 mousePos;
 
void main()
{
	// Como voy a seguir la misma lógica de cambiar el color según la distancia al mouse,
	// puedo copiar el código del vertex shader.

	// copy position so we can work with it.
	vec2 pos = vPosition;
    
	// direction vector from mouse position to vertex position.
	vec2 dir = pos.xy - mousePos;
    
	// distance between the mouse position and vertex position.
	float dist =  sqrt(dir.x * dir.x + dir.y * dir.y);
    
	// check vertex is within mouse range.
	if(dist > 0.0 && dist < mouseRange) {
		
		// normalise distance between 0 and 1.
		float distNorm = dist / mouseRange;
        
		// flip it so the closer we are the greater the repulsion.
		distNorm = 1.0 - distNorm;

		outputColor = mouseColor - sin(distNorm/2);
	}
	else{
		outputColor = mouseColor;
	}		
}
```

## Video de Funcionamiento
Este semestre tocó poner a chambear al OBS otra vez xd  
[Link al video](https://youtu.be/3ZO6eaCmZVE)