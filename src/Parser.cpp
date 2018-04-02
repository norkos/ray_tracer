#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cassert>
#include <algorithm>    

#include "Parser.hpp"

namespace rt{

bool Parser::parse_model(const char* model){

    std::ifstream file(model);
    if (file.is_open()){
        std::string line;
        Material* material = nullptr;
        char name[100];
        long int line_number = 1;
        while (getline (file, line)){
            if(line[0] == 'v'){
                double x=0,y=0,z=0;
                if(sscanf(line.c_str(),"vn %lf %lf %lf",&x, &y, &z) == 3){
                    normal_vertices.push_back(Vector(x,y,z));
                }
                else if( sscanf(line.c_str(),"v %lf %lf %lf",&x, &y, &z) == 3){
                    vertices.push_back(Vector(x,y,z));
                }
                else if( sscanf(line.c_str(),"vt %lf %lf %lf",&x, &y, &z) == 3){
                    texture_vertices.push_back(Vector(x,y,z));
                }
            }else if(line[0] == 'f'){
                add_triangle(line_number, line, material);
            }else if(sscanf(line.c_str(),"usemtl %s",name) == 1){
                material = &materials[name];
            }
            line_number++;
        }
        return true;
    }

    return false;
}

bool Parser::parse_material(const char* material){
    std::string line;

    std::ifstream file(material);
    if (file.is_open()){
        char name[100];
        double a,b,c;

        while (getline (file, line)){
            if(sscanf(line.c_str(),"newmtl %s",name) == 1){
                materials[name] = Material();
            }
            else if(sscanf(line.c_str(),"    Ns %lf", &a) == 1){
                materials[name].specular_exp = a;
            }
            else if(sscanf(line.c_str(),"    Tr %lf", &a) == 1){
                materials[name].transparency = a;
            }
            else if(sscanf(line.c_str(),"    Tf %lf %lf %lf", &a, &b, &c) == 3){
                materials[name].transmision_filter = Vector(a, b, c);
            }
            else if(sscanf(line.c_str(),"    Ka %lf %lf %lf", &a, &b, &c) == 3){
                materials[name].ambient = Vector(a, b, c);
            }
            else if(sscanf(line.c_str(),"    Kd %lf %lf %lf", &a, &b, &c) == 3){
                materials[name].diffuse = Vector(a, b, c);
            }
            else if(sscanf(line.c_str(),"    Ks %lf %lf %lf", &a, &b, &c) == 3){
                materials[name].specular = Vector(a, b, c);
            }
        }
        return true;
    }

    return false;
}


bool Parser::parse(const char* model, const char* material){
    return parse_material(material) && parse_model(model);
}

Triangle Parser::build_triangle(long int line_number, Material* material, int vertex0, int texture0, int normal0, 
        int vertex1, int texture1, int normal1, 
        int vertex2, int texture2, int normal2){
    Triangle result;
    result.vertex[0] = vertices[vertex0 -1];
    result.vertex[1] = vertices[vertex1 -1];
    result.vertex[2] = vertices[vertex2 -1];

    result.normal[0] = normal_vertices[normal0 -1];
    result.normal[1] = normal_vertices[normal1 -1];
    result.normal[2] = normal_vertices[normal2 -1];

    if(texture0 > 0){
        result.texture[0] = texture_vertices[texture0 -1];
    }

    if(texture1 > 0){
        result.texture[1] = texture_vertices[texture1 -1];
    }

    if(texture2 > 0){
        result.texture[2] = texture_vertices[texture2 -1];
    }

    result.material = material;
    result.line = line_number;

    return result;
}

void Parser::add_triangle(long int line_number, const std::string& line, Material* material){
    int pointers[4][3];
    memset(pointers, 0, sizeof(pointers));

    int result = sscanf(line.c_str(),"%*s %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i",
        &pointers[0][0], &pointers[0][1], &pointers[0][2],
        &pointers[1][0], &pointers[1][1], &pointers[1][2],
        &pointers[2][0], &pointers[2][1], &pointers[2][2],
        &pointers[3][0], &pointers[3][1], &pointers[3][2]);

    int one_point_matched = 3;
    if (result < one_point_matched){
        memset(pointers, 0, sizeof(pointers));
        result = sscanf(line.c_str(),"%*s %i//%i %i//%i %i//%i %i//%i",
            &pointers[0][0], &pointers[0][2],
            &pointers[1][0], &pointers[1][2],
            &pointers[2][0], &pointers[2][2],
            &pointers[3][0], &pointers[3][2]);
    }
        
    triangles.push_back(build_triangle(line_number, material,
            pointers[0][0], pointers[0][1], pointers[0][2],
            pointers[1][0], pointers[1][1], pointers[1][2],
            pointers[2][0], pointers[2][1], pointers[2][2]));

    const int four_triples = 12;
    const int four_pairs = 8;
    if(result == four_pairs || result == four_triples){
        triangles.push_back(build_triangle(line_number, material,
            pointers[2][0], pointers[2][1], pointers[2][2],
            pointers[3][0], pointers[3][1], pointers[3][2],
            pointers[0][0], pointers[0][1], pointers[0][2]));
    }
}

}