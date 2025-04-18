#ifndef _SIM_H_
#define _SIM_H_

#include <cmath>
#include "Planet.h"
#include "Vector2.h"
#include <iostream>

class Simulation{

    private:
    const double G = 6.67430e-11;
    const int PHYSICS_STEPS = 100;
    const int WINDOW_WIDTH = 1600;
    const int WINDOW_HEIGHT = 900;
    const int VIEW_WIDTH = 16;
    const int VIEW_HEIGHT = 9;    

    public:
    void calculate_gravity(Planet*, int, double);
    Vector2 calculate_orbit_velocity(Planet&, Planet&);
    void run();

};


#endif