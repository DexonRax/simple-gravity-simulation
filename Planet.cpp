#include "Planet.h"

Planet::Planet(double mass, double radius, Vector2 pos, Vector2 vel, Vector2 acc, sf::Color color){
    m_Mass = mass;
    m_Radius = radius;
    m_Position = pos;
    m_Acceleration = acc;
    m_Velocity = vel;
    m_Color = color;
}


double Planet::getMass(){
    return m_Mass;
}

double Planet::getRadius(){
    return m_Radius;
}

Vector2 Planet::getPosition(){
    return m_Position;
}

Vector2 Planet::getVelocity(){
    return m_Velocity;
}

Vector2 Planet::getAcceleration(){
    return m_Acceleration;
}

sf::Color Planet::getColor(){
    return m_Color;
}



void Planet::setMass(double m){
    m_Mass = m;
}

void Planet::setRadius(double r){
    m_Radius = r;
}

void Planet::setPosition(Vector2 vec){
    m_Position = vec;
}

void Planet::setVelocity(Vector2 vec){
    m_Velocity = vec;
}

void Planet::setAcceleration(Vector2 vec){
    m_Acceleration = vec;
}

void Planet::setColor(sf::Color color){
    m_Color = color;
}