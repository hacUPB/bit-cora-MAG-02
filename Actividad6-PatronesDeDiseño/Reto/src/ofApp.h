#pragma once

#include "ofMain.h"

// CLASE PADRE
class Shape {
private:
	ofColor color;
	float size;
	int key;

public:
	//Constructor
	Shape(ofColor _color, float _size, int _key)
		: color(_color)
		, size(_size)
		, key(_key) { };

	//Destructor
	virtual ~Shape() { };

	// --- Métodos Virtuales ---
	virtual void draw(float x, float y) = 0;
	virtual void fun() = 0;

	// --- Métodos Comunes ---
	void randomColor() {
		color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
	}

	// --- Getters y Setters ---
	ofColor getColor() const { return color; }
	void setColor(ofColor c) { color = c; }

	float getSize() const { return size; }
	void setSize(float s) { size = s; }
};

// SUBCLASES
class Triangle : Shape {

};

class Square : Shape {

};

class Circle : Shape {
public:
	//Constructor
	Circle(ofColor color, float size, int key) : Shape(color, size, key) {}

	void draw(float x, float y) override {
		ofSetColor(getColor());
		ofDrawCircle(x, y, getSize());
	}

	void fun() override {
		//Cambiar de tamaño a uno rándom
		setSize(ofRandom(10, 50));
	}
};

class Other : Shape {

};

// OPEN FRAMEWORKS
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
