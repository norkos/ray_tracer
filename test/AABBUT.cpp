#include <gtest/gtest.h>
#include <AABB.hpp>
namespace GT = ::testing;

namespace rt
{

namespace ut
{

TEST(AABBUT, extend){
    //  given
    AABB first(Vector(-1,-2, 3), Vector(5,6,3));
    AABB second(Vector(0,0,0), Vector(3,2,3));

     //  when
    first.extend(second);

    // then
    ASSERT_EQ(Vector(-1,-2,0), first.get_min());
    ASSERT_EQ(Vector(5,6,3), first.get_max());
}

TEST(AABBUT, octet){
    //  given
    AABB aabb(Vector(-4,-4, -4), Vector(4,4,4));

     //  when
    std::vector<AABB> result = aabb.split_to_octet();
    AABB reconstruction;

    // then
    ASSERT_EQ(8, result.size());
    for(auto& elem: result){
        Vector size = elem.get_max() - elem.get_min();
        ASSERT_EQ(4, size.getX());
        ASSERT_EQ(4, size.getY());
        ASSERT_EQ(4, size.getZ());

        reconstruction.extend(elem);
    }

    ASSERT_EQ(aabb.get_min(), reconstruction.get_min());
    ASSERT_EQ(aabb.get_max(), reconstruction.get_max());
}

TEST(AABBUT, contains){
    //  given
    AABB aabb(Vector(-4,-4, -4), Vector(4,4,4));
    std::vector<AABB> result = aabb.split_to_octet();

    // then
    for(auto& elem: result){
        ASSERT_TRUE(aabb.fully_contains(elem));
    }
}

TEST(AABBUT, not_contains){
    //  given
    AABB aabb(Vector(-4,-4, -4), Vector(4,4,4));
    AABB external(Vector(-8,-8, -8), Vector(0,0,0));

    // then
    ASSERT_FALSE(aabb.fully_contains(external));
}

}
}