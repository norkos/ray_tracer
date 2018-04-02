#pragma once

#include <Color.hpp>
#include <Triangle.hpp>
#include <Ray.hpp>
#include <Vector.hpp>
#include <Light.hpp>
#include <OctTree.hpp>

#include <memory>
#include <vector>

namespace rt{

class Scene{
    const OctTree& oct_tree;
    double ambient_light;
    double accuracy;

    std::vector<Light> lights;
    
public:

    Scene(double accurancy, const OctTree& tree);

    Color get_color(Ray& ray, int x, int y) const;


    private:

    double saturate(double x) const;

    Color getColorAt(Triangle& triangle, const Vector& intersection_position, const Vector& view_direction) const;
    
    Vector get_reflection_direction(const Vector& winning_object_normal, const Vector& intersecting_ray_direction) const;
};

}