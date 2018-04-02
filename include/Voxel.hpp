#pragma once
#include <Vector.hpp>
#include <vector>

namespace rt{

struct Voxel{
    Vector start;
    Vector middle;
    std::vector<int> triangles;
};
}