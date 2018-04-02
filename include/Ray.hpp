#pragma once
#include <Vector.hpp>

namespace rt{

class Ray{
    Vector origin, direction;

public:
    Ray(const Vector& a, const Vector& b):origin(a), direction(b){}

    const Vector& getOrigin() const { return origin; }
    const Vector& getDirection() const { return direction; }
};
}