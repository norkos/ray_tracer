#include <AABB.hpp>

namespace rt{

void AABB::extend(const AABB& box){
    min.x = std::min(min.x, box.min.x);
    min.y = std::min(min.y, box.min.y);
    min.z = std::min(min.z, box.min.z);

    max.x = std::max(max.x, box.max.x);
    max.y = std::max(max.y, box.max.y);
    max.z = std::max(max.z, box.max.z);
}

bool AABB::contains(const Vector& v) { 
    return v.getX() >= min.getX() && v.getX() <= max.getX() && 
    v.getY() >= min.getY() && v.getY() <= max.getY() &&
    v.getZ() >= min.getZ() && v.getZ() <= max.getZ();
}


bool AABB::fully_contains(const AABB& aabb) { 
    return contains(aabb.min) && contains(aabb.max); 
}

std::vector<AABB> AABB::split_to_octet(){
    std::vector<AABB> nodes(8);

    Vector distance = (max - min)* 0.5;
    Vector center = min + distance;

    nodes[0] = {
        min,
        center
    };
 
    nodes[1] = {
        min + Vector(distance.getX(), 0 ,0),
        center + Vector(distance.getX(), 0 ,0)
    };

    nodes[2] = {
        min + Vector(0, distance.getY() ,0),
        center + Vector(0, distance.getY() ,0)
    };

    nodes[3] = {
        min + Vector(distance.getX(), distance.getY() ,0),
        center + Vector(distance.getX(), distance.getY() ,0)
    };

    nodes[4] = {
        min + Vector(0, 0 ,distance.getZ()),
        center + Vector(0, 0 ,distance.getZ()),
    };

    nodes[5] = {
        min + Vector(distance.getX(), 0 ,distance.getZ()),
        center + Vector(distance.getX(), 0 ,distance.getZ()),
    };

    nodes[6] = {
        min + Vector(0,distance.getY() ,distance.getZ()),
        center + Vector(0,distance.getY() ,distance.getZ()),
    };

    nodes[7] = {
        min + Vector(distance.getX(),distance.getY() ,distance.getZ()),
        center + Vector(distance.getX(),distance.getY() ,distance.getZ()),
    };

    return nodes;
}
}