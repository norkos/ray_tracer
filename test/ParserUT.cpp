#include <gtest/gtest.h>
#include "Parser.hpp"

namespace rt {
namespace ut {

namespace GT = ::testing;

const char* model = "../resources/vertex_ut_input.model";
const char* material = "../resources/vertex_ut_input.material";

TEST(paser_ut, traiangles_size)
{
    //  given
    Parser sut;

    //  when    
    sut.parse(model,material);

    //  then
    uint triangles_size = 11;
    EXPECT_EQ(triangles_size, sut.get_triangles().size());
}

TEST(paser_ut, traiangle_textures)
{
    //  given
    Parser sut;

    //  when
    sut.parse(model,material);

    //  then
    EXPECT_EQ(Vector(2.0,2.0,2.0), sut.get_triangles()[0].texture[0]);
    EXPECT_EQ(Vector(1.0,1.0,1.0), sut.get_triangles().back().texture[1]);
}

TEST(paser_ut, traiangle_values)
{
    //  given
    Parser sut;

    //  when
    sut.parse(model,material);

    //  then
    EXPECT_FLOAT_EQ(-143.3909, sut.get_triangles()[1].vertex[0].getZ());
    EXPECT_FLOAT_EQ(171.0719, sut.get_triangles()[2].vertex[0].getX());
}

TEST(paser_ut, vertices_size)
{
    //  given
    Parser sut;

    //  when
    sut.parse(model,material);

    //  then
    uint vertices_size = 8;
    EXPECT_EQ(vertices_size, sut.get_vertices().size());
}

TEST(paser_ut, vertex_values)
{
    //  given
    Parser sut;

    //  when
    sut.parse(model,material);

    //  then
    double x  = 446.6624, y= 118.1102, z = -147.3279;
    const Vector& result = sut.get_vertices()[0];   
    EXPECT_FLOAT_EQ(x, result.getX());  
    EXPECT_FLOAT_EQ(y, result.getY());
    EXPECT_FLOAT_EQ(z, result.getZ());
}

TEST(paser_ut, texture_vertices_size)
{
    //  given
    Parser sut;

    //  when
    sut.parse(model,material);

    //  then
    uint vertices_size = 2;
    EXPECT_EQ(vertices_size, sut.get_texture_vertices().size());
}

TEST(paser_ut, normal_vertices_size)
{
    //  given
    Parser sut;

    //  when
    sut.parse(model,material);

    //  then
    uint vertices_size = 6;
    EXPECT_EQ(vertices_size, sut.get_normal_vertices().size());
}

TEST(paser_ut, normal_vertex_values)
{
    //  given
    Parser sut;

    //  when
    sut.parse(model,material);

    //  then
    double x = -1.0000, y = 0.0000, z = -0.0000;
    const Vector& result = sut.get_normal_vertices()[1];    
    EXPECT_FLOAT_EQ(x, result.getX());  
    EXPECT_FLOAT_EQ(y, result.getY());
    EXPECT_FLOAT_EQ(z, result.getZ());
}

TEST(paser_ut, material)
{
    //  given
    Parser sut;
    std::string name= "wire_006135113";

    //  when    
    sut.parse(model,material);

    //  then
    EXPECT_EQ(32, sut.get_materials()[name].specular_exp);
    EXPECT_EQ(3, sut.get_materials()[name].transparency);
    EXPECT_EQ(Vector(1,1,1), sut.get_materials()[name].transmision_filter);
    EXPECT_EQ(Vector(0.0314, 0.0314, 0.5333), sut.get_materials()[name].ambient);
    EXPECT_EQ(Vector(0.0315, 0.0315, 0.5334), sut.get_materials()[name].diffuse);
    EXPECT_EQ(Vector(0.3500, 0.3500, 0.3500), sut.get_materials()[name].specular);
}

TEST(paser_ut, triangle_material)
{
    //  given
    Parser sut;

    //  when    
    sut.parse(model,material);

    //  then
    EXPECT_EQ(32, sut.get_triangles()[4].material->specular_exp);
}

}
}