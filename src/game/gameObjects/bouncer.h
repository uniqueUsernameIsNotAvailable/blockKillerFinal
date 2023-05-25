#ifndef BOUNCER_H
#define BOUNCER_H

#include "typicalObject.h"
#include <list>

class Bouncer;

class IObserver {
public:
    virtual void handleBallXYMove(Bouncer &ball) = 0;
};

class IObservalble {
public:
    virtual void attach(IObserver *observer) = 0;

    virtual void detach(IObserver *observer) = 0;
};

class Bouncer : public MoveObject, public IObservalble {
public:
    Bouncer(float x0, float y0, float r, float speed);

    ~Bouncer();

    float getL() const;

    float getR() const;

    float getU() const;

    float getD() const;

    float getRad() const;

    void setRad(float rad);

    void attach(IObserver *observer);

    void detach(IObserver *observer);

    void upd();

private:
    std::list<IObserver *> observers;

    void callObservers();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif