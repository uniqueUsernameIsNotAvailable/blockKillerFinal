#ifndef TYPICAL_OBJECT_H
#define TYPICAL_OBJECT_H

#include <SFML/Graphics.hpp>

class TypicalObject : public sf::Drawable {
public:

    TypicalObject(sf::Vector2f pos, sf::Shape *shp, const sf::Color &color);

    sf::Vector2f getPosition() const;

    void setPosition(const sf::Vector2f &pos);

    virtual float getL() const = 0;

    virtual float getR() const = 0;

    virtual float getU() const = 0;

    virtual float getD() const = 0;

    bool isIntersection(const TypicalObject &other) const;

protected:
    sf::Shape *shape;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};


class MoveObject : public TypicalObject {
public:

    MoveObject(sf::Vector2f pos, sf::Shape *shape, float accSpeed, sf::Vector2f speed, const sf::Color &color);

    virtual void upd();

    sf::Vector2f getSpeed() const;

    void setSpeed(const sf::Vector2f &v);

    void setSpeedX(float vx);

    void setSpeedY(float vy);

    float getAccSpeed() const;

protected:
    sf::Vector2f speed;
    float accSpeed;
};


#endif
