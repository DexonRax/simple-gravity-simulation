#ifndef _PLANET_H_
#define _PLANET_H_

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Planet {
    private:
    double m_Mass;
    double m_Radius;
    Vector2 m_Position;
    Vector2 m_Velocity;
    Vector2 m_Acceleration;
    sf::Color m_Color;

    public:
    Planet(double, double, Vector2, Vector2, Vector2, sf::Color);
    double getMass();
    double getRadius();
    Vector2 getPosition();
    Vector2 getVelocity();
    Vector2 getAcceleration();
    sf::Color getColor();

    void setMass(double);
    void setRadius(double);
    void setPosition(Vector2);
    void setVelocity(Vector2);
    void setAcceleration(Vector2);
    void setColor(sf::Color);

};

#endif