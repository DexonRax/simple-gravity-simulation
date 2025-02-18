#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

/*-----------------------------------*/
/*     Simple Gravity Simulator      */
/* Based on Newton's Gravity Theorem */
/*      and Kepler's Third Law       */
/*-----------------------------------*/


const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;
const int VIEW_WIDTH = 16;
const int VIEW_HEIGHT = 9;
const double G = 6.67430e-11;
const int PHYSICS_STEPS = 100;

struct Vector2 {
    double x, y;

    Vector2 operator+(const Vector2& other) const {
        return {x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    Vector2 operator/(double scalar) const {
        return {x / scalar, y / scalar};
    }

    double magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 normalized() const {
        double mag = magnitude();
        if (mag == 0) return {0, 0};
        return {x / mag, y / mag};
    }
};


struct Planet {
    double m_mass;
    double m_radius;
    Vector2 m_position;
    Vector2 m_velocity;
    Vector2 m_acceleration;
    sf::Color m_color;
};

void calculate_gravity(Planet* planets, int planetCount, double deltaTime) {
    for (size_t i = 0; i < planetCount; ++i) {
        planets[i].m_acceleration = {0, 0};

        for (size_t j = 0; j < planetCount; ++j) {
            if (i == j) continue;

            Vector2 direction = planets[j].m_position - planets[i].m_position;
            double distance = direction.magnitude();
            if (distance < planets[i].m_radius + planets[j].m_radius) continue;

            double forceMagnitude = G * planets[j].m_mass / (distance * distance);
            planets[i].m_acceleration = planets[i].m_acceleration + direction.normalized() * forceMagnitude;
        }

        planets[i].m_velocity = planets[i].m_velocity + planets[i].m_acceleration * deltaTime;
        planets[i].m_position = planets[i].m_position + planets[i].m_velocity * deltaTime;
    }
}

Vector2 calculate_orbit_velocity(Planet &p1, Planet &p2){
    double angle = atan2(p1.m_position.y - p2.m_position.y, p1.m_position.x - p2.m_position.x);
    std::cout<<angle<<"\n";
    Vector2 direction = p1.m_position - p2.m_position;
    double distance = direction.magnitude();
    Vector2 vel = {sin(angle)*sqrt(G * p2.m_mass / distance), cos(angle)*sqrt(G * p2.m_mass / distance)};
    return vel;
}


int main(){

    double drawScale = 2.0;
    double timeScale = 75.0;
    double initialViewScale = 5.0e5;
    double viewScale = initialViewScale;
    double deltaTime = 0.01;
    double viewX = 0.0;
    double viewY = 0.0;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity Simulation");
    sf::Clock deltaTimeClock;
    sf::View view(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT));
    view.setCenter(sf::Vector2f(0,0));

    int viewPlanet = -1;
    view.setSize(VIEW_WIDTH * viewScale, VIEW_HEIGHT * viewScale);

    int planetCount = 7;
    Planet planets[planetCount] = {
        {1.9885e15, 5000.0, {0, 0}, {0, 0}, {0, 0}, sf::Color::Yellow},
        {1.0e10, 1000.0, {22000, 0}, {0, 6}, {0, 0}, sf::Color::Blue},
        {1.0e7, 800.0, {-16000, 0}, {0, 6}, {0, 0}, sf::Color::Green},
        {1.0e12, 600.0, {0, 100000}, {0, 6}, {0, 0}, sf::Color::Cyan},
		{1.0, 250.0, {0, 101000}, {0, 0}, {0, 0}, sf::Color::White},
        {1.0e12, 600.0, {0, 500000}, {0, 6}, {0, 0}, sf::Color::Cyan},
		{1.0, 250.0, {0, 510000}, {0, 0}, {0, 0}, sf::Color::White} 

    };

    planets[1].m_velocity = calculate_orbit_velocity(planets[1], planets[0]);
    planets[2].m_velocity = calculate_orbit_velocity(planets[2], planets[0]);
    planets[3].m_velocity = calculate_orbit_velocity(planets[3], planets[0]);
    planets[4].m_velocity = calculate_orbit_velocity(planets[4], planets[0]) + calculate_orbit_velocity(planets[4], planets[3]);

    planets[5].m_velocity = calculate_orbit_velocity(planets[5], planets[0]);
    planets[6].m_velocity = calculate_orbit_velocity(planets[6], planets[0]) + calculate_orbit_velocity(planets[6], planets[5]);


   /*
    const int planetCount = 8;
    Planet planets[planetCount] = {
        {1.989e30, 696340, {0, 0}, {0, 0}, {0, 0}, sf::Color::Yellow}, // Sun
        {3.301e23, 2439.7, {57900000, 0}, {0, 47.87}, {0, 0}, sf::Color(169, 169, 169)}, // Mercury
        {4.867e24, 6051.8, {108200000, 0}, {0, 35.02}, {0, 0}, sf::Color(255, 165, 0)}, // Venus
        {5.972e24, 6371, {149600000, 0}, {0, 29.78}, {0, 0}, sf::Color::Blue}, // Earth
        {6.417e23, 3389.5, {227900000, 0}, {0, 24.07}, {0, 0}, sf::Color::Red}, // Mars
        {1.898e27, 69911, {778500000, 0}, {0, 13.07}, {0, 0}, sf::Color(218, 165, 32)}, // Jupiter
        {5.683e26, 58232, {1429000000, 0}, {0, 9.69}, {0, 0}, sf::Color(210, 180, 140)}, // Saturn
        {8.681e25, 25362, {2871000000, 0}, {0, 6.81}, {0, 0}, sf::Color(173, 216, 230)}  // Uranus
    };

    planets[1].m_velocity = calculate_orbit_velocity(planets[1], planets[0]);
    planets[2].m_velocity = calculate_orbit_velocity(planets[2], planets[0]);
    planets[3].m_velocity = calculate_orbit_velocity(planets[3], planets[0]);
    planets[4].m_velocity = calculate_orbit_velocity(planets[4], planets[0]);
    planets[5].m_velocity = calculate_orbit_velocity(planets[5], planets[0]);
    planets[6].m_velocity = calculate_orbit_velocity(planets[6], planets[0]);
    planets[7].m_velocity = calculate_orbit_velocity(planets[7], planets[0]);
    */



    std::cout<<"initialization finalized\n";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Right && viewPlanet < planetCount - 1) {
                    viewPlanet++;
                } else if (event.mouseButton.button == sf::Mouse::Left && viewPlanet > -1) {
                    viewPlanet--;
                }
            }
        }

        for (int step = 0; step < PHYSICS_STEPS; ++step) {
            calculate_gravity(planets, planetCount, deltaTime * timeScale);
        }

        if(viewPlanet != -1){
            viewScale = planets[viewPlanet].m_radius * 20;
            view.setSize(VIEW_WIDTH * viewScale, VIEW_HEIGHT * viewScale);
            view.setCenter(planets[viewPlanet].m_position.x, planets[viewPlanet].m_position.y); 
        }else{
            //viewScale = initialViewScale;
            //view.setSize(VIEW_WIDTH * viewScale, VIEW_HEIGHT * viewScale);
            float velX = 0.0f, velY = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                velX -= 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                velX += 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                velY -= 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                velY += 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
                viewScale += viewScale * 0.002;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
                viewScale -= viewScale * 0.002;

            std::cout<<"view scale: "<<viewScale<<"\n";

            float length = sqrt(pow(velX, 2) + pow(velY, 2));
            if (length != 0) {
                velX = velX / length;
                velY = velY / length;
            }

            viewX += velX * viewScale * deltaTime;
            viewY += velY * viewScale * deltaTime;

            view.setCenter(sf::Vector2f(round(viewX), round(viewY)));
            view.setSize(VIEW_WIDTH * viewScale, VIEW_HEIGHT * viewScale);
        }

        window.clear();
        
        window.setView(view);
            
        sf::CircleShape planetDrawable;
        

        for (int i = 0; i < planetCount; i++){
            planetDrawable.setRadius(planets[i].m_radius * drawScale);
            planetDrawable.setOrigin(planets[i].m_radius * drawScale, planets[i].m_radius * drawScale);
            planetDrawable.setPosition(sf::Vector2f(planets[i].m_position.x, planets[i].m_position.y));
            planetDrawable.setFillColor(planets[i].m_color);
            window.draw(planetDrawable);
            
        }

        window.display();

        deltaTime = deltaTimeClock.restart().asSeconds();

    }

    return 0;
}
