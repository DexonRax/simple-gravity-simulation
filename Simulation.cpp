#include "Simulation.h"

void Simulation::calculate_gravity(Planet* planets, int planetCount, double deltaTime) {
    for (int i = 0; i < planetCount; ++i) {
        planets[i].setAcceleration({0,0});

        for (int j = 0; j < planetCount; ++j) {
            if (i == j) continue;

            Vector2 direction = planets[j].getPosition() - planets[i].getPosition();
            double distance = direction.magnitude();
            if (distance < planets[i].getRadius() + planets[j].getRadius()) continue;

            double forceMagnitude = G * planets[j].getMass() / (distance * distance);
            planets[i].setAcceleration(planets[i].getAcceleration() + direction.normalized() * forceMagnitude);
        }

        planets[i].setVelocity(planets[i].getVelocity() + planets[i].getAcceleration() * deltaTime);
        planets[i].setPosition(planets[i].getPosition() + planets[i].getVelocity() * deltaTime);
    }
}

Vector2 Simulation::calculate_orbit_velocity(Planet &p1, Planet &p2){
    double angle = atan2(p1.getPosition().y - p2.getPosition().y, p1.getPosition().x - p2.getPosition().x);
    std::cout<<angle<<"\n";
    Vector2 direction = p1.getPosition() - p2.getPosition();
    double distance = direction.magnitude();
    Vector2 vel = {sin(angle)*sqrt(G * p2.getMass() / distance), cos(angle)*sqrt(G * p2.getMass() / distance)};
    return vel;
}

void Simulation::run(){

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

    int planetCount = 8;
    Planet planets[8]  = {
        Planet(1.9885e15, 8000.0, {0, 0}, {0, 0}, {0, 0}, sf::Color::Yellow),
        Planet(1.0e10, 1000.0, {42000, 0}, {0, 6}, {0, 0}, sf::Color::Blue),
        Planet(1.0e7, 800.0, {-36000, 0}, {0, 6}, {0, 0}, sf::Color::Green),
        Planet(1.0e12, 600.0, {0, 120000}, {0, 6}, {0, 0}, sf::Color::Cyan),
        Planet(1.0, 250.0, {0, 121000}, {0, 0}, {0, 0}, sf::Color::White),
        Planet(1.0e12, 600.0, {0, 500000}, {0, 6}, {0, 0}, sf::Color::Cyan),
        Planet(1.0, 250.0, {0, 510000}, {0, 0}, {0, 0}, sf::Color::White),
        Planet(1.0, 450.0, {40000, 35000}, {0, -2}, {0, 0}, sf::Color::Red) 
    };

    planets[1].setVelocity(calculate_orbit_velocity(planets[1], planets[0]));
    planets[2].setVelocity(calculate_orbit_velocity(planets[2], planets[0]));
    planets[3].setVelocity(calculate_orbit_velocity(planets[3], planets[0]));
    planets[4].setVelocity(calculate_orbit_velocity(planets[4], planets[0]) + calculate_orbit_velocity(planets[4], planets[3]));

    planets[5].setVelocity(calculate_orbit_velocity(planets[5], planets[0]));
    planets[6].setVelocity(calculate_orbit_velocity(planets[6], planets[0]) + calculate_orbit_velocity(planets[6], planets[5]));

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
            viewScale = planets[viewPlanet].getRadius() * 20;
            view.setSize(VIEW_WIDTH * viewScale, VIEW_HEIGHT * viewScale);
            view.setCenter(planets[viewPlanet].getPosition().x, planets[viewPlanet].getPosition().y); 
        }else{
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
                viewScale -= viewScale * 0.002;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
                viewScale += viewScale * 0.002;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)){
                timeScale += timeScale * 0.001;
                std::cout<<"time scale: "<<timeScale<<"\n";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)){
                timeScale -= timeScale * 0.001;
                std::cout<<"time scale: "<<timeScale<<"\n";
            }


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
            planetDrawable.setRadius(planets[i].getRadius() * drawScale);
            planetDrawable.setOrigin(planets[i].getRadius() * drawScale, planets[i].getRadius() * drawScale);
            planetDrawable.setPosition(sf::Vector2f(planets[i].getPosition().x, planets[i].getPosition().y));
            planetDrawable.setFillColor(planets[i].getColor());
            window.draw(planetDrawable);
            
        }

        window.display();

        deltaTime = deltaTimeClock.restart().asSeconds();
        std::cout<<"dt: "<<deltaTime<<"\n";
    }

}
