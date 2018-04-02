#pragma once
#include <Vector.hpp>
#include <Color.hpp>

namespace rt{

struct Light{
    Vector position;
  	Vector diffuse;  
	Vector specular;
};
}