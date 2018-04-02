#include <Scene.hpp>

#include <Vector.hpp>
#include <Triangle.hpp>
#include <Ray.hpp>

#include <iostream>
#include <limits>
namespace rt {

double Scene::saturate(double x) const
{
  return fmax(0.0, fmin(1.0, x));
}

Color Scene::getColorAt(Triangle& triangle, const Vector& intersection_position, const Vector& viewer_position) const{

    Vector normal = triangle.getNormalAt(intersection_position);
    const Material* material = triangle.material;
    Vector final_color = material->ambient * 0.3;

    for(const auto& light: lights){
        Vector from_light_color;

        Vector L = (light.position - intersection_position).normalize();
        Vector V = (viewer_position - intersection_position).normalize();
        Vector H = (L + V).normalize();

        double NdotL = normal.dotProduct(L);
        double NdotH = normal.dotProduct(H);

        double light_distance = 1;//(light.position - intersection_position).magnitude();

        // diffuse
        double intensity = saturate(NdotL);

        Vector diffuse_color = material->ambient * material->diffuse * light.diffuse * intensity / light_distance;
        final_color = final_color + diffuse_color;

        //  specular
        intensity = pow( saturate( NdotH ), material->specular_exp );

        Vector specular_color = material->ambient * material->specular *  light.specular * intensity / light_distance;
        final_color = final_color + specular_color;
    }

    return {final_color.x, final_color.y, final_color.z, 0.0};;
}


Color Scene::get_color(Ray& ray, int x, int y) const
{
    Vector intersection_place;
    double distance = std::numeric_limits<double>::max();
    Triangle* triangle = oct_tree.get_root().intersection(ray, intersection_place, distance);

    if(triangle == nullptr){
        return {1,0,0,0};
    }

    Vector intersection_direction; //
    Color result = getColorAt(*triangle, intersection_place, ray.getOrigin());
    //printf ("(x=%d,y=%d) line %ld : %lf %lf %lf \n", x, y, triangle->line, result.red, result.green, result.blue);

    return result;
}

Scene::Scene(double acc, const OctTree& tree): oct_tree(tree){

    lights.push_back(
      Light{
          { 231.82174, 81.69966, -27.78259 },
          { 1.0, 1.0, 1.0 },
          { 1.0, 1.0, 1.0 }
    });

    lights.push_back(
      Light{
          { 200, 80.0, 0 },
          { 0.3, 0.3, 0.3 },
          { 0.3, 0.3, 0.3 }
    });

    lights.push_back(
      Light{
          { 200, 80.0, 80 },
          { 0.3, 0.3, 0.3 },
          { 0.3, 0.3, 0.3 }
    });

    lights.push_back(
      Light{
          { 200, 80.0, 160 },
          { 0.3, 0.3, 0.3 },
          { 0.3, 0.3, 0.3 }
    });

}

}
