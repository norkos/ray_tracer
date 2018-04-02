#pragma once
#include <math.h> 
#include <iostream>

namespace rt{

class Vector{

public:
    double x, y, z;

    Vector(): x(0), y(0), z(0) {}
    Vector(double i, double j, double k): x(i), y(j), z(k) {}

    void print(){
        printf ("Vector with X(%f) Y(%f) Z(%f) \n", x, y,z);
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    Vector normalize() const {
        auto size = sqrt(x * x + y * y + z * z);
        if(size == 0){
            return *this;
        }
        return Vector(x/size, y/size, z/size); 
    }

    double magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    double dotProduct(const Vector& b) const {
        return x * b.x + y * b.y + z * b.z;
    }

    Vector crossProduct(const Vector& b) const {
        return Vector(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }

    Vector operator-() const {
        return Vector(-x, -y, -z);
    }

    friend Vector operator+(const Vector& a, const Vector& b) {
        return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    friend Vector operator-(const Vector& a, const Vector& b){
        return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    friend bool operator==(const Vector& a, const Vector& b){
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    friend Vector operator*(const Vector& a, double scalar){
        return Vector(a.x *scalar, a.y *scalar , a.z *scalar);
    }

    friend Vector operator*(const Vector& a, const Vector& b){
        return Vector(a.x *b.x, a.y *b.y , a.z *b.z);
    }


    friend Vector operator*(double scalar, const Vector& a){
        return Vector(a.x *scalar, a.y *scalar , a.z *scalar);
    }

    friend Vector operator/(double scalar, const Vector& a){
        return Vector(scalar/ a.x, scalar / a.y , scalar / a.z);
    }

    friend Vector operator/(const Vector& a, double scalar){
        return Vector(a.x / scalar, a.y / scalar, a.z / scalar);
    }

    friend bool operator>(const Vector& a, double scalar){
        return a.x > scalar && a.y > scalar &&  a.z > scalar;
    }
};
}
