#pragma once
#include <vector>
#include <iostream>

#include <Vector.hpp>
#include <Triangle.hpp>
#include <Material.hpp>

#include <map>

namespace rt{

class Parser{
public:
    bool parse(const char* model, const char* material);
    std::vector<Vector>& get_vertices() { return vertices; }
    std::vector<Vector>& get_normal_vertices() { return normal_vertices; }
    std::vector<Vector>& get_texture_vertices() { return texture_vertices; }
    std::vector<Triangle>& get_triangles() { return triangles; }
    std::map<std::string, Material>& get_materials() { return materials; }

private:
    std::vector<Vector> vertices;
    std::vector<Vector> normal_vertices;
    std::vector<Vector> texture_vertices;
    std::vector<Triangle> triangles;
    std::map<std::string, Material> materials;

    bool parse_model(const char* model);
    bool parse_material(const char* material);

    Triangle build_triangle(long int line_number, Material* material, int vertex0, int texture0, int normal0, 
        int vertex1, int texture1, int normal1, 
        int vertex2, int texture2, int normal2);
    void add_triangle(long int line_number, const std::string& line, Material* material);
};
}