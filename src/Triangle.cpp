#include "Triangle.hpp"
#include <cmath> 
#include <iostream>

namespace rt{

AABB Triangle::make_box() const {
    return AABB( 
        Vector(std::min(vertex[0].x, std::min(vertex[1].x, vertex[2].x)),
               std::min(vertex[0].y, std::min(vertex[1].y, vertex[2].y)),
               std::min(vertex[0].z, std::min(vertex[1].z, vertex[2].z))),

        Vector(std::max(vertex[0].x, std::max(vertex[1].x, vertex[2].x)),
               std::max(vertex[0].y, std::max(vertex[1].y, vertex[2].y)),
               std::max(vertex[0].z, std::max(vertex[1].z, vertex[2].z)))
        );
}

void Triangle::print(){
    printf ("Triangle with A(%f,%f,%f) B(%f,%f,%f) C(%f,%f,%f) \n",
        vertex[0].getX(), vertex[0].getY(), vertex[0].getZ(),
        vertex[1].getX(), vertex[1].getY(), vertex[1].getZ(),
        vertex[2].getX(), vertex[2].getY(), vertex[2].getZ() );
}

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool Triangle::intersection(const Ray& ray, Vector& intersection_point, double& distance) const  
{
    const double EPSILON = 0.00000001; 
    Vector edge1 = vertex[1] - vertex[0];
    Vector edge2 = vertex[2] - vertex[0];

    Vector h = ray.getDirection().crossProduct(edge2);
    double w = edge1.dotProduct(h);

    if (w > -EPSILON && w < EPSILON){
        return false;
    }

    double f = 1.0 / w;
    Vector s = ray.getOrigin() - vertex[0];
    double u = f * s.dotProduct(h);

    if(u< 0.0 || u > 1.0){
        return false;
    }

    Vector q = s.crossProduct(edge1);
    double v = f * ray.getDirection().dotProduct(q);
    
    if(v< 0.0 || u + v > 1.0){
        return false;
    }

    distance = f * edge2.dotProduct(q);
    if(distance < 0.0){
        return false;
    }

    intersection_point = ray.getOrigin() + ray.getDirection() * distance;

    return true;
}

Vector Triangle::getNormalAt(const Vector& v) const  {
    
    double p0 = get_area(vertex[1], vertex[2], v);
    double p1 = get_area(vertex[2], vertex[0], v);
    double p2 = get_area(vertex[1], vertex[0], v);

    return (p0 * normal[0] + p1 * normal[1] + p2 * normal[2]) / get_area();
}

//  Heron
double Triangle::get_area(const Vector& v1, const Vector& v2, const Vector& v3) const {
    Vector edge1 = v2 - v1;
    Vector edge2 = v3 - v1;
    Vector edge3 = v2 - v3;

    double a = edge1.magnitude();
    double b = edge2.magnitude();
    double c = edge3.magnitude();

    double p = (a + b + c) * 0.5;
    double result = p * (p-a) * (p-b) * (p-c);

    if(result < 0.0){
        throw 1;
    }

    return sqrt(result);
}
}
