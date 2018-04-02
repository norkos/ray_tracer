#include <gtest/gtest.h>
#include <Vector.hpp>
namespace GT = ::testing;

namespace rt
{

namespace ut
{

const double PRECISON=0.001;

TEST(VectorUT, normalize){
    //  given
    Vector v(3,4,5);

    // when
    auto result = v.normalize();

    // then
    ASSERT_NEAR(0.424, result.getX(), PRECISON);
    ASSERT_NEAR(0.566, result.getY(), PRECISON);
    ASSERT_NEAR(0.707, result.getZ(), PRECISON);
}

TEST(VectorUT, normalize_empty){
    //  given
    Vector a(0,0,0);

    // when
    auto result = a.normalize();

    // then
    ASSERT_EQ(0, result.getX());
    ASSERT_EQ(0, result.getY());
    ASSERT_EQ(0, result.getZ());
}

TEST(VectorUT, negative){
    //  given
    Vector a(3,4,5);

    // when
    auto result = -a;

    // then
    ASSERT_EQ(-a.getX(), result.getX());
    ASSERT_EQ(-a.getY(), result.getY());
    ASSERT_EQ(-a.getZ(), result.getZ());
}

TEST(VectorUT, dotProduct){
    //  given
    Vector a(3,4,5);
    Vector b(-3,-4,10);

    //  when
    auto dotProduct = a.dotProduct(b);

    //  then
    ASSERT_EQ(25, dotProduct);
}

TEST(VectorUT, crossProduct){
     //  given
    Vector a(1,2,3);
    Vector b(3,2,-1);

    //  when
    auto result = a.crossProduct(b);

    //  then
    ASSERT_EQ(-8, result.getX());
    ASSERT_EQ(10, result.getY());
    ASSERT_EQ(-4, result.getZ());
}

TEST(VectorUT, add){
     //  given
    Vector a(1,2,3);
    Vector b(3,1,-1);

    //  when
    auto result = a + b;

    //  then
    ASSERT_EQ(4, result.getX());
    ASSERT_EQ(3, result.getY());
    ASSERT_EQ(2, result.getZ());
}

TEST(VectorUT, minus){
     //  given
    Vector a(1,2,3);
    Vector b(3,1,-1);

    //  when
    auto result = a - b;

    //  then
    ASSERT_EQ(-2, result.getX());
    ASSERT_EQ(1, result.getY());
    ASSERT_EQ(4, result.getZ());
}


TEST(VectorUT, multiply){
     //  given
    Vector a(1,2,3);
    double scalar = 3;

    //  when
    auto result = a * scalar;

    //  then
    ASSERT_EQ(3, result.getX());
    ASSERT_EQ(6, result.getY());
    ASSERT_EQ(9, result.getZ());
}

}
}