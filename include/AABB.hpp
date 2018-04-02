#pragma once
#include <Vector.hpp>
#include <Ray.hpp>
#include <vector>

namespace rt{

class AABB{
        Vector min;
        Vector max;
    public:
        AABB() {}
        AABB(const Vector& a, const Vector& b) : min(a), max(b) {}
        std::vector<AABB> split_to_octet();
        bool fully_contains(const AABB&);
        void extend(const AABB& box);

        const Vector& get_min() const { return min;}
        const Vector& get_max() const { return max;}

    private:
        bool contains(const Vector&);
};
}