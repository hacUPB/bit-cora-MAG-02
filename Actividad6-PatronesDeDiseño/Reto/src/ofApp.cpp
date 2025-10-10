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
	speedMult = 1;

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
    if (event == "normal") {
        setState(new NormalState());
    }
    else if (event == "attend") {
        setState(new AttendState());
    }
    else if (event == "ignore") {
        setState(new IgnoreState());
	}
	else if (event == "up") {
		setState(new UpState());
	}
	else if (event == "down") {
		setState(new DownState());
	}
}

void NormalState::update(Particle* particle) {
    particle->position += particle->velocity;
}

void NormalState::onEnter(Particle* particle) {
    particle->velocity = ofVec2f(ofRandom(-0.5f, 0.5f), ofRandom(-0.5f, 0.5f));
	particle->velocity *= particle->speedMult;
}

void AttendState::update(Particle* particle) {
	ofVec2f mousePosition(((ofApp *)ofGetAppPtr())->mouseX, ((ofApp *)ofGetAppPtr())->mouseY);
	ofVec2f direction = mousePosition - particle->position;
	direction.normalize();

	particle->velocity += direction * 0.01 * particle->speedMult;

	particle->position += particle->velocity;

	if (particle->position.distance(mousePosition) <= 1) {
		particle->color = ofColor(0); //Esto porque borrar las partículas requeriría un proceso más largo y ya está demasiado tarde.
	}
}

void IgnoreState::update(Particle* particle) {
	particle->position += particle->velocity;
}

void UpState::update(Particle* particle) {
	particle->position += particle->velocity;
	particle->velocity *= 1.005f;
}

void DownState::update(Particle * particle) {
	particle->position += particle->velocity;
	particle->velocity *= 0.995f;
}

Particle* ParticleFactory::createParticle(const std::string& type) {
    Particle* particle = new Particle();

    if (type == "planet") {
        particle->size = ofRandom(4, 6);
        particle->color = ofColor(0, 0, 255); //Planetas Azules
    }
    else if (type == "comet") {
        particle->size = ofRandom(2, 3);
		particle->color = ofColor(ofRandom(255)); //Cometas en escala de Grises
		particle->speedMult = 3; //Pa' que anden con Nitro
    }
    else if (type == "star") {
        particle->size = ofRandom(11, 14);
        particle->color = ofColor(255); //Estrellas blancas bien bellas
		particle->speedMult = 0.01f; //Pa' que se muevan muuuucho más lento
    }
    return particle;
}


void ofApp::setup() {
    ofBackground(0);
    // Crear partículas usando la fábrica
    for (int i = 0; i < 75; ++i) {
        Particle* p = ParticleFactory::createParticle("comet");
        particles.push_back(p);
        addObserver(p);
    }

    for (int i = 0; i < 15; ++i) {
        Particle* p = ParticleFactory::createParticle("planet");
        particles.push_back(p);
        addObserver(p);
    }

	for (int i = 0; i < 5; ++i) {
		Particle * p = ParticleFactory::createParticle("star");
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
    if (key == 'a') {
        notify("attend");
		cout << "Tecla \"a\" presionada. Estado AttendState.\n";
    }
    else if (key == 'i') {
        notify("ignore");
		cout << "Tecla \"i\" presionada. Estado IgnoreState.\n";
	}
    else if (key == 'n') {
        notify("normal");
		cout << "Tecla \"n\" presionada. Estado NormalState.\n";
    }
	else if (key == 'u') {
		notify("up");
		cout << "Tecla \"u\" presionada. Estado UpState.\n";
	}
	else if (key == 'd') {
		notify("down");
		cout << "Tecla \"d\" presionada. Estado DownState.\n";
	}
}
