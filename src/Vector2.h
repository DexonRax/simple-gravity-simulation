#ifndef _VEC_2_H_
#define _VEC_2_H_
#include <cmath>

class Vector2 {
    public:
    double x, y;

    Vector2 operator+(const Vector2&) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(double scalar) const;
    Vector2 operator/(double scalar) const;
    double magnitude() const;
    Vector2 normalized() const;
};

#endif