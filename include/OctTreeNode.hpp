#pragma once
#include <AABB.hpp>
#include <Triangle.hpp>

#include <vector>

namespace rt {

namespace tree{
const int MAX_NUMER_OF_ELEMENTS = 16;
const int OCTET = 8;
}

class OctTreeNode{
    AABB aabb;
    std::vector<OctTreeNode> nodes;
    std::vector<Triangle*> primitives;

public:
    OctTreeNode() {}
    OctTreeNode(const AABB& box): aabb(box) {}

    void add(Triangle& triangle);
    void split();
    bool intersection(const Ray& ray, double& distance) const;
    Triangle* intersection(const Ray& ray, Vector& point, double& distance) const;
    
    const std::vector<OctTreeNode>& get_nodes() { return nodes;}
    const std::vector<Triangle*>& get_primitives() { return primitives;}
};
}