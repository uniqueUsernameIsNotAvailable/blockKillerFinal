#include "typicalObject.h"


TypicalObject::TypicalObject(sf::Vector2f pos, sf::Shape *shp, const sf::Color &color) {
    shape = shp;
    shape->setPosition(pos);
    shape->setFillColor(color);
}

sf::Vector2f TypicalObject::getPosition() const { return shape->getPosition(); }

void TypicalObject::setPosition(const sf::Vector2f &pos) { shape->setPosition(pos); }

bool TypicalObject::isIntersection(const TypicalObject &other) const {
    return this->getR() >= other.getL() && this->getL() <= other.getR() &&
           this->getD() >= other.getU() && this->getU() <= other.getD();
}

MoveObject::MoveObject(sf::Vector2f pos, sf::Shape *form, float accSpeed, sf::Vector2f speed, const sf::Color &color) :
        TypicalObject(pos, form, color), speed(speed), accSpeed(accSpeed) {}

void MoveObject::upd() { shape->move(speed); }

sf::Vector2f MoveObject::getSpeed() const { return speed; }

void MoveObject::setSpeed(const sf::Vector2f &v) { speed = v; }

void MoveObject::setSpeedX(float vx) { speed.x = vx; }

void MoveObject::setSpeedY(float vy) { speed.y = vy; }

float MoveObject::getAccSpeed() const { return accSpeed; }