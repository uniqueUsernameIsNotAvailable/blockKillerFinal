#ifndef TARGET_H
#define TARGET_H

#include "bouncer.h"


class Target : public TypicalObject, public IObserver {
public:
    Target(float x0, float y0, float w, float h, int hp);

    ~Target();

    float getW() const;

    float getH() const;

    void setSize(const sf::Vector2f &size);

    float getL() const;

    float getR() const;

    float getU() const;

    float getD() const;

    bool isHealth() const;

    void onHit();

    void handleBallXYMove(Bouncer &bouncer);

    Target *clone();

    static unsigned getPoints();

    static void clearPoints();

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void updColor();

    int health;
    static unsigned points;
};

// Prototype Pattern Impl
class TargetMaker {
public:
    TargetMaker(float w, float h);

    ~TargetMaker();

    Target *getTarget(int type) const;

private:
    Target *softCover;
    Target *medCover;
    Target *hardCover;
};

#endif
