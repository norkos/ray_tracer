#include <gtest/gtest.h>
#include <OctTreeNode.hpp>
namespace GT = ::testing;

namespace rt
{

namespace ut
{

Triangle create_triangle(){
    Vector a(1, 0, 0);
    Vector b(0, 1, 0);
    Vector c(0, 0, 1);

    Triangle triangle;
    triangle.vertex[0] = a;
    triangle.vertex[1] = b;
    triangle.vertex[2] = c;

    return triangle;
}

TEST(OctTreeNodeUT, too_less_primitives){
    //  given
    int triangle_size = tree::MAX_NUMER_OF_ELEMENTS - 1;
    std::vector<Triangle> triangles(triangle_size);

    //  when
    OctTreeNode sut;
    for(Triangle tr: triangles){
        sut.add(tr);
    }
    sut.split();

    // then
    ASSERT_EQ(0, sut.get_nodes().size());
    ASSERT_EQ(triangle_size, sut.get_primitives().size());
}

TEST(OctTreeNodeUT, basic_split_done){
    //  when
    OctTreeNode sut;
    std::vector<Triangle> triangles(tree::MAX_NUMER_OF_ELEMENTS);
    for(int i =0; i < tree::MAX_NUMER_OF_ELEMENTS; i++){
        triangles[i] = create_triangle();;
        sut.add(triangles[i]);
    }

    //  when
    sut.split();

    // then
    ASSERT_EQ(tree::OCTET, sut.get_nodes().size());
}

}
}