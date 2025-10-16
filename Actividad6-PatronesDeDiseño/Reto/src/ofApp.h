#pragma once

#include "ofMain.h"
#include <vector>
#include <string>


//OBSERVER
class Observer {
public:
    virtual void onNotify(const std::string& event) = 0;
};

class Subject {
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
protected:
    void notify(const std::string& event);
private:
    std::vector<Observer*> observers;
};


// ----- ESTADOS -----
class Particle; //Esta línea se tiene que poner antes de crear los estados :p

class State {
public:
	virtual void update(Particle * particle) = 0;
	virtual void onEnter(Particle * particle) { }
	virtual void onExit(Particle * particle) { }
	virtual ~State() = default;
};
//ESTADOS PLANET & COMET
class NormalState : public State {
public:
	void update(Particle * particle) override;
	virtual void onEnter(Particle * particle) override;
};

class AttendState : public State {
public:
	void update(Particle * particle) override;
};

class IgnoreState : public State {
public:
	void update(Particle * particle) override;
};

class UpState : public State {
public:
	void update(Particle * particle) override;
};

class DownState : public State {
public:
	void update(Particle * particle) override;
};


//PARTÍCULA
class Particle : public Observer {
public:
    Particle();
    ~Particle();

    void update();
    void draw();
    void onNotify(const std::string& event) override;
    void setState(State* newState);

    ofVec2f position;
    ofVec2f velocity;
    float size;
    ofColor color;

	float speedMult;

private:
    State* state;
};


//FACTORY
class ParticleFactory {
public:
    static Particle* createParticle(const std::string& type);
};


//GENERALES
class ofApp : public ofBaseApp, public Subject {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
private:
    std::vector<Particle*> particles;
};
