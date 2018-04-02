#pragma once
#include <Vector.hpp>

namespace rt {

struct Material{
    double specular_exp;
    double transparency;
    Vector transmision_filter;

    Vector ambient;
    Vector diffuse;
    Vector specular; 
};
}