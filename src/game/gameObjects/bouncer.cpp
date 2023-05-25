#include "bouncer.h"


Bouncer::Bouncer(float x0, float y0, float r, float speed) :
        MoveObject(sf::Vector2f(x0, y0), new sf::CircleShape(), speed,
                   sf::Vector2f(speed, speed), sf::Color::Red) {
    shape->setOrigin(r, r);
    setRad(r);
}

Bouncer::~Bouncer() {
    if (shape != nullptr)
        delete dynamic_cast<sf::CircleShape *>(shape);
    shape = nullptr;
}

float Bouncer::getRad() const { return dynamic_cast<sf::CircleShape *>(shape)->getRadius(); }

void Bouncer::setRad(float rad) { dynamic_cast<sf::CircleShape *>(shape)->setRadius(rad); }

float Bouncer::getL() const { return getPosition().x - getRad(); }

float Bouncer::getR() const { return getPosition().x + getRad(); }

float Bouncer::getU() const { return getPosition().y - getRad(); }

float Bouncer::getD() const { return getPosition().y + getRad(); }

void Bouncer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*dynamic_cast<sf::CircleShape *>(shape), states);
}


//Observer Pattern Impl
void Bouncer::attach(IObserver *observer) { observers.push_back(observer); }

void Bouncer::detach(IObserver *observer) { observers.remove(observer); }

void Bouncer::callObservers() {
    for (IObserver *iter: observers)
        iter->handleBallXYMove(*this);
}

void Bouncer::upd() {
    MoveObject::upd();
    callObservers();
}