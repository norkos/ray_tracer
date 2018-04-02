#include <gtest/gtest.h>
#include <Triangle.hpp>
namespace GT = ::testing;

namespace rt
{

namespace ut
{

TEST(TriangleUT, simple_area){
    //  given
    Vector a(0, 0, 0);
    Vector b(2, 0, 0);
    Vector c(0, 2, 0);

     //  when
    Triangle sut;
    sut.vertex[0] = a;
    sut.vertex[1] = b;
    sut.vertex[2] = c;

    auto result = sut.get_area();

    // then
    EXPECT_FLOAT_EQ(2, result);
}

TEST(TriangleUT, get_normal){
    //  given
    Vector a(-2, 0, 0);
    Vector b(0, 2, 0);
    Vector c(2, 0, 0);

    Vector n1(4, 4, 4);
    Vector n2(8, 3, 5);
    Vector n3(10, 10, 10);

     //  when
    Triangle sut;
    sut.vertex[0] = a;
    sut.vertex[1] = b;
    sut.vertex[2] = c;

    sut.normal[0] = n1;
    sut.normal[1] = n2;
    sut.normal[2] = n3;

    //  point
    Vector p(0, 1, 0);

    auto result = sut.getNormalAt(p);

    // then
    EXPECT_FLOAT_EQ(7.5, result.getX());
    EXPECT_FLOAT_EQ(5.0, result.getY());
    EXPECT_FLOAT_EQ(6.0, result.getZ());
}

TEST(TriangleUT, simple_area_2){
    //  given
    Vector a(0, -2, -2);
    Vector b(0, 2, -2);
    Vector c(0, 1, 3);

     //  when
    Triangle sut;
    sut.vertex[0] = a;
    sut.vertex[1] = b;
    sut.vertex[2] = c;

    auto result = sut.get_area();

    // then
    EXPECT_FLOAT_EQ(10, result);

}

TEST(TriangleUT, make_AABB){
    //  given
    Vector a(1, -1, 0);
    Vector b(0, 1, 0);
    Vector c(0, 0, 1);

     //  when
    Triangle sut;
    sut.vertex[0] = a;
    sut.vertex[1] = b;
    sut.vertex[2] = c;

    auto result = sut.make_box();

    // then
    ASSERT_EQ(Vector(0,-1,0), result.get_min());
    ASSERT_EQ(Vector(1,1,1), result.get_max());
}

}
}