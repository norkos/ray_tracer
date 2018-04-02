#include <OctTree.hpp>
#include <memory>

namespace rt{

OctTree::OctTree(std::vector<Triangle>& triangles) {
    for(auto& triangle: triangles){
        root.add(triangle);
    }
    root.split();
}
}