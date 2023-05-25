#include "reflector.h"

Reflector::Reflector(float x0, float y0, float w, float h, float accSpeed) :
        MoveObject(sf::Vector2f(x0, y0), new sf::RectangleShape(),
                   accSpeed, sf::Vector2f(0.f, 0.f), sf::Color::White) {
    setSize(sf::Vector2f(w, h));
    dynamic_cast<sf::RectangleShape *>(shape)->setOrigin(w / 2.f, h / 2.f);
}

Reflector::~Reflector() {
    if (shape != nullptr)
        delete dynamic_cast<sf::RectangleShape *>(shape);
    shape = nullptr;
}

float Reflector::getWidth() const { return dynamic_cast<sf::RectangleShape *>(shape)->getSize().x; }

float Reflector::getHeight() const { return dynamic_cast<sf::RectangleShape *>(shape)->getSize().y; }

void Reflector::setSize(const sf::Vector2f &size) { dynamic_cast<sf::RectangleShape *>(shape)->setSize(size); }

float Reflector::getR() const { return getPosition().x + getWidth() / 2.f; }

float Reflector::getL() const { return getPosition().x - getWidth() / 2.f; }

float Reflector::getU() const { return getPosition().y - getHeight() / 2.f; }

float Reflector::getD() const { return getPosition().y + getHeight() / 2.f; }

void Reflector::moveL() { setSpeedX(-accSpeed); }

void Reflector::moveR() { setSpeedX(accSpeed); }

void Reflector::stay() { setSpeedX(0.f); }

void Reflector::handleBallXYMove(Bouncer &ball) {
    if (!isIntersection(ball)) return;

    if (ball.getPosition().x < getPosition().x)
        ball.setSpeedX(-ball.getAccSpeed());
    else
        ball.setSpeedX(ball.getAccSpeed());

    ball.setSpeedY(-ball.getAccSpeed());
}

void Reflector::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*dynamic_cast<sf::RectangleShape *>(shape), states);
}