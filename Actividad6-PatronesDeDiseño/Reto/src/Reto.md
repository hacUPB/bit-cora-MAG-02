# Reto

Desarrolla un proyecto de arte generativo interactivo en tiempo real. Diferente, lo más que puedas al caso de estudio.

## Requisitos

- Utilizando **C++** y **openFrameworks**.
- Aplica el patrón de diseño **Observer**.
- Aplica el patrón de diseño **Factory**.
- Aplica el patrón de diseño **State**.
- Realiza pruebas desde el inicio del desarrollo para garantizar el correcto funcionamiento de la aplicación.

## Desarrollo
Okay, modo reto, que rinda hoy x Diosito

> Spoiler: No rindió :c

Tocó hacer cambios drásticos a la idea original, la cual dejaría aquí en la bitácora pero se ve muy feo lol. La pondré en un archivo a parte, creo.  
En el proyecto final, estos fueron los:

### Estados
```cpp
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
```
Estos estados pretenden simular la interacción de planetas y objetos del espacio con un agujero negro *(el mouse)* o también permiten ignorarlo, pues. También hay 2 estados donde la velocidad de todas las partículas aumentará o disminuirá gradualmente.

### Observer
En la parte el Observer, no hubo cambios, ya que el observer del caso de estudio cumplía perfectamente con lo necesario para este proyecto.
```cpp
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
```

### Factory
El proceso de Factory es el que, según yo, más destaca en este caso, porque se encarga de asignar a las distintas partículas un nuevo valor que cambia notablemente su comportamiento, el `speedMult`. La idea de este valor es representar que un objeto tiene más masa que los otros, así que es más difícil hacer a este objeto ganar velocidad.
```cpp
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
```

Por último, el [video de funcionamiento](https://youtu.be/gLLot8-mwNw). Y creo que ya con eso queda todo, wooo! La verdad estuvo algo regular el proyecto, pero siento que es una cuestión de que tuve una idea demasiado ambiciosa que no fui capaz de realizar :\