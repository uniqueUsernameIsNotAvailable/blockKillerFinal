#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "typicalObject.h"
#include "bouncer.h"


class Reflector : public MoveObject, public IObserver {
public:
    Reflector(float x0, float y0, float w, float h, float accSpeed);

    ~Reflector();

    float getWidth() const;

    float getHeight() const;

    float getL() const;

    float getR() const;

    float getU() const;

    float getD() const;

    void moveL();

    void moveR();

    void stay();

    void setSize(const sf::Vector2f &size);

    void handleBallXYMove(Bouncer &ball);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
