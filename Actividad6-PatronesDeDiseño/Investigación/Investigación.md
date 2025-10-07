# Experiencia de Aprendizaje 6: Patrones de Diseño

## Sesión 2: análisis de un caso de estudio
Ahora te voy a presentar un caso de estudio que utiliza los patrones de diseño que hemos revisado. Ten presente que no voy a partir el código en múltiples archivos para que puedas hacer las pruebas y configuración rápidamente, pero en la práctica deberías hacerlo por orden y buenas prácticas de programación. Te dejo esa tarea a ti.

`ofApp.h`
```cpp
#pragma once

#include "ofMain.h"
#include <vector>
#include <string>

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

class Particle;

class State {
public:
    virtual void update(Particle* particle) = 0;
    virtual void onEnter(Particle* particle) {}
    virtual void onExit(Particle* particle) {}
    virtual ~State() = default;
};

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

private:
    State* state;
};


class NormalState : public State {
public:
    void update(Particle* particle) override;
    virtual void onEnter(Particle* particle) override;
};


class AttractState : public State {
public:
    void update(Particle* particle) override;
};

class RepelState : public State {
public:
    void update(Particle* particle) override;
};

class StopState : public State {
public:
    void update(Particle* particle) override;
};

class ParticleFactory {
public:
    static Particle* createParticle(const std::string& type);
};

class ofApp : public ofBaseApp, public Subject {
    public:
        void setup();
        void update();
        void draw();
        void keyPressed(int key);
private:
    std::vector<Particle*> particles;
};
```

`ofApp.cpp`
```cpp
#include "ofApp.h"

void Subject::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify(const std::string& event) {
    for (Observer* observer : observers) {
        observer->onNotify(event);
    }
}

Particle::Particle() {
    // Inicializar propiedades
    position = ofVec2f(ofRandomWidth(), ofRandomHeight());
    velocity = ofVec2f(ofRandom(-0.5f, 0.5f), ofRandom(-0.5f, 0.5f));
    size = ofRandom(2, 5);
    color = ofColor(255);

    state = new NormalState();
}

Particle::~Particle() {
    delete state;
}

void Particle::setState(State* newState) {
    if (state != nullptr) {
        state->onExit(this);
        delete state;
    }
    state = newState;
    if (state != nullptr) {
        state->onEnter(this);
    }
}

void Particle::update() {
    if (state != nullptr) {
        state->update(this);
    }
    // Mantener las partículas dentro de la ventana
    if (position.x < 0 || position.x > ofGetWidth()) velocity.x *= -1;
    if (position.y < 0 || position.y > ofGetHeight()) velocity.y *= -1;
}

void Particle::draw() {
    ofSetColor(color);
    ofDrawCircle(position, size);
}

void Particle::onNotify(const std::string& event) {
    if (event == "attract") {
        setState(new AttractState());
    }
    else if (event == "repel") {
        setState(new RepelState());
    }
    else if (event == "stop") {
        setState(new StopState());
    }
    else if (event == "normal") {
        setState(new NormalState());
    }
}

void NormalState::update(Particle* particle) {
    particle->position += particle->velocity;
}

void NormalState::onEnter(Particle* particle) {
    particle->velocity = ofVec2f(ofRandom(-0.5f, 0.5f), ofRandom(-0.5f, 0.5f));
}

void AttractState::update(Particle* particle) {
    ofVec2f mousePosition(((ofApp*)ofGetAppPtr())->mouseX, ((ofApp*)ofGetAppPtr())->mouseY);
    ofVec2f direction = mousePosition - particle->position;
    direction.normalize();
    particle->velocity += direction * 0.05;
    ofClamp(particle->velocity.x, -3, 3);
    particle->position += particle->velocity * 0.2;
}

void RepelState::update(Particle* particle) {
    ofVec2f mousePosition(((ofApp*)ofGetAppPtr())->mouseX, ((ofApp*)ofGetAppPtr())->mouseY);
    ofVec2f direction = particle->position - mousePosition;
    direction.normalize();
    particle->velocity += direction * 0.05;
    ofClamp(particle->velocity.x, -3, 3);
    particle->position += particle->velocity * 0.2;
}

void StopState::update(Particle* particle) {
    particle->velocity.x = 0;
    particle->velocity.y = 0;
}

Particle* ParticleFactory::createParticle(const std::string& type) {
    Particle* particle = new Particle();

    if (type == "star") {
        particle->size = ofRandom(2, 4);
        particle->color = ofColor(255, 0, 0);
    }
    else if (type == "shooting_star") {
        particle->size = ofRandom(3, 6);
        particle->color = ofColor(0, 255, 0);
        particle->velocity *= 3;
    }
    else if (type == "planet") {
        particle->size = ofRandom(5, 8);
        particle->color = ofColor(0, 0, 255);
    }
    return particle;
}


void ofApp::setup() {
    ofBackground(0);
    // Crear partículas usando la fábrica
    for (int i = 0; i < 100; ++i) {
        Particle* p = ParticleFactory::createParticle("star");
        particles.push_back(p);
        addObserver(p);
    }

    for (int i = 0; i < 5; ++i) {
        Particle* p = ParticleFactory::createParticle("shooting_star");
        particles.push_back(p);
        addObserver(p);
    }

    for (int i = 0; i < 10; ++i) {
        Particle* p = ParticleFactory::createParticle("planet");
        particles.push_back(p);
        addObserver(p);
    }

}


void ofApp::update() {
    for (Particle* p : particles) {
        p->update();
    }
}


void ofApp::draw() {
    for (Particle* p : particles) {
        p->draw();
    }
}

void ofApp::keyPressed(int key) {
    if (key == 's') {
        notify("stop");
    }
    else if (key == 'a') {
        notify("attract");
    }
    else if (key == 'r') {
        notify("repel");
    }
    else if (key == 'n') {
        notify("normal");
    }
}
```

Ahora te pediré que te tomes un tiempo para analizar el código y entender su funcionamiento.
- **¿Qué hace el patrón observer en este caso?**  
Se encarga de notificar a las partículas suscritas sobre cambios de estado causados por el usuario, específicamente con el teclado. Esto nos permitiría, si cambiamos el código, escoger qué partículas obedecen a qué botones del teclado, por decir así.
- **¿Qué hace el patrón factory en este caso?**  
Simplemente crea las partículas y les asigna por defecto el estado `normal`. Crea 3 tipos de partícula, y todas quedan suscritas al observer (porque todas usan ), pero se puede cambiar el código para que no lo estén.
- **¿Qué hace el patrón state en este caso?**  
Es el que define el comportamiento de las partículas según el estado en el que estén, y se divide en `normal`, `attract`, `repel`, y `stop`.

Experimenta con el código y realiza algunas modificaciones para entender mejor su funcionamiento. Por ejemplo:

- **Adiciona un nuevo tipo de partícula.**  
Voy a crear una partícula que *no* esté suscrita a los estados pre-establecidos.
    ```cpp
    //Dentro de ParticleFactory::createParticle():
    else if (type == "comet") {
    particle->size = 2;
    particle->color = ofColor(ofRandom(150, 255));
    }

    //Dentro de ofApp::setup():
    for (int i = 0; i < 50; ++i) {
    Particle* p = ParticleFactory::createParticle("comet");
    particles.push_back(p);
    }
    ```
    Esta partícula es de un tamaño constante `2`, tiene un color en escala de grises, y **no** está suscrita al observer, por lo que no reaciona a presionar el teclado.

- **Adiciona un nuevo estado.**  
Va. Quiero hacer un estado en el que todas las partículas se muevan en una misma dirección. ¿Cómo? No sé. Lo averiguaremos :p
    ```cpp
    //Primero que nada, en ofApp.h:
    class OrderState : public State {
    public:
        void update(Particle* particle) override;
    };
    ```
- **Modifica el comportamiento de las partículas.**
- **Crea otros eventos para notificar a las partículas.**