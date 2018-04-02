#pragma once
#include <Triangle.hpp>
#include <OctTreeNode.hpp>
#include <Triangle.hpp>

#include <vector>

namespace rt{

class OctTree{
    OctTreeNode root;
public:
    OctTree(std::vector<Triangle>& triangles);
    const OctTreeNode& get_root() const { return root;}
};
}