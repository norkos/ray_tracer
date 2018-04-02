#pragma once
#include <Vector.hpp>
#include <Color.hpp>
#include <Ray.hpp>
#include <AABB.hpp>
#include <Material.hpp>
#include <memory>

namespace rt{

class Triangle  {

public:
    Vector vertex[3];
    Vector normal[3];
    Vector texture[3];
    Material* material = nullptr;
    Color c{0.5,0.5,0.5,0};
    long int line;

    const Color& getColor() const  {
        return c;
    }


    //  Heron
    double get_area(const Vector& v1, const Vector& v2, const Vector& v3) const;
    double get_area() const {
        return get_area(vertex[0], vertex[1], vertex[2]);
    }

    void print();
    
    Vector getNormalAt(const Vector& v) const;

    bool intersection(const Ray& ray, Vector& intersection_point, double& distance) const;

    AABB make_box() const;
};
}