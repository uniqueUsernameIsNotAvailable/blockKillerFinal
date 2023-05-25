#include "target.h"


Target::Target(float x0, float y0, float w, float h, int hp) :
        TypicalObject(sf::Vector2f(x0, y0), new sf::RectangleShape(), sf::Color::Yellow) {
    health = (hp <= 3 && hp > 0) ? hp : 3;
    updColor();
    setSize(sf::Vector2f(w, h));
    dynamic_cast<sf::RectangleShape *>(shape)->setOrigin(w / 2.f, h / 2.f);
}

Target::~Target() {
    if (shape != nullptr)
        delete dynamic_cast<sf::RectangleShape *>(shape);
    shape = nullptr;
}

void Target::setSize(const sf::Vector2f &size) { dynamic_cast<sf::RectangleShape *>(shape)->setSize(size); }

float Target::getW() const { return dynamic_cast<sf::RectangleShape *>(shape)->getSize().x; }

float Target::getH() const { return dynamic_cast<sf::RectangleShape *>(shape)->getSize().y; }

float Target::getR() const { return getPosition().x + getW() / 2.f; }

float Target::getL() const { return getPosition().x - getW() / 2.f; }

float Target::getU() const { return getPosition().y - getH() / 2.f; }

float Target::getD() const { return getPosition().y + getH() / 2.f; }

bool Target::isHealth() const { return health != 0; }

unsigned Target::points = 0;

unsigned Target::getPoints() { return points; }

void Target::clearPoints() { Target::points = 0; }

void Target::updColor() {
    switch (health) {
        case 3:
            shape->setFillColor(sf::Color::Red);
            break;
        case 2:
            shape->setFillColor(sf::Color::Yellow);
            break;
        case 1:
            shape->setFillColor(sf::Color::Cyan);
            break;
        default:
            break;
    }
}

void Target::onHit() {
    health--;
    updColor();
    points++;
}

void Target::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*dynamic_cast<sf::RectangleShape *>(shape), states);
}

void Target::handleBallXYMove(Bouncer &bouncer) {
    if (!isIntersection(bouncer)) return;

    onHit();

    //ovlp means overlap
    float ovlpL = bouncer.getR() - getL();
    float ovlpR = getR() - bouncer.getL();
    float ovlpU = bouncer.getD() - getU();
    float ovlpD = getD() - bouncer.getU();

    bool isFromLeft = std::abs(ovlpL) < std::abs(ovlpR);
    bool isFromUp = std::abs(ovlpU) < std::abs(ovlpD);

    float minOvLapX = isFromLeft ? ovlpL : ovlpR;
    float minOvLapY = isFromUp ? ovlpU : ovlpD;

    if (std::abs(minOvLapX) < std::abs(minOvLapY))
        bouncer.setSpeedX(isFromLeft ? -bouncer.getAccSpeed() : bouncer.getAccSpeed());
    else
        bouncer.setSpeedY(isFromUp ? -bouncer.getAccSpeed() : bouncer.getAccSpeed());
}

Target *Target::clone() {
    return new Target(getPosition().x, getPosition().y, getW(), getH(), health);
}

// Prototype Pattern Impl
TargetMaker::TargetMaker(float w, float h) {
    softCover = new Target(0.f, 0.f, w, h, 1);
    medCover = new Target(0.f, 0.f, w, h, 2);
    hardCover = new Target(0.f, 0.f, w, h, 3);
}

TargetMaker::~TargetMaker() {
    delete softCover;
    delete medCover;
    delete hardCover;
}

Target *TargetMaker::getTarget(int type) const {
    Target *out = nullptr;

    switch (type) {
        case 3:
            out = hardCover->clone();
            break;
        case 2:
            out = medCover->clone();
            break;
        case 1:
            out = softCover->clone();
            break;
        default:
            break;
    }
    return out;
}