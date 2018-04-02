#include <gtest/gtest.h>
#include <Color.hpp>
namespace GT = ::testing;

namespace rt
{

namespace ut
{

TEST(ColorUT, add){
     //  given
    Color a{1,2,3,1};
    Color b{3,1,-1,2};

    //  when
    auto result = a + b;

    //  then
    ASSERT_EQ(4, result.red);
    ASSERT_EQ(3, result.green);
    ASSERT_EQ(2, result.blue);
    ASSERT_EQ(1, result.special);
}

TEST(ColorUT, multiply){
     //  given
    Color  a{1,2,3,3};
    double scalar = 3;

    //  when
    auto result = a * scalar;

    //  then
    ASSERT_EQ(3, result.red);
    ASSERT_EQ(6, result.green);
    ASSERT_EQ(9, result.blue);
    ASSERT_EQ(3, result.special);
}

TEST(ColorUT, multiplyColors){
     //  given
    Color  a{1,2,3,3};
    Color  b{2,3,4,2};

    //  when
    auto result = a * b;

    //  then
    ASSERT_EQ(2, result.red);
    ASSERT_EQ(6, result.green);
    ASSERT_EQ(12, result.blue);
    ASSERT_EQ(3, result.special);
}

}
}