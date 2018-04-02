#include <OctTreeNode.hpp>
#include <limits>

namespace rt {

void OctTreeNode::add(Triangle& triangle){
    aabb.extend(triangle.make_box());
    primitives.push_back(&triangle);
}

Triangle* OctTreeNode::intersection(const Ray& ray, Vector& point, double& distance) const{
    Triangle* winner = nullptr;

    Vector winner_intersection_point;
    double winner_to_triangle = std::numeric_limits<double>::max();

    double to_box_distance = std::numeric_limits<double>::max();
    if(intersection(ray, to_box_distance)){

        if(to_box_distance > distance){
            //  no sense to make here any checks as we alerady have closest object
            return nullptr;
        }

        //  try to find closest triangle
        double distance_to_triangle = std::numeric_limits<double>::max();
        Vector triangle_intersection_point;
        for(Triangle* triangle: primitives){
            
            bool intersect = triangle->intersection(ray, triangle_intersection_point, distance_to_triangle);
            if(intersect && distance_to_triangle < winner_to_triangle){
                winner = triangle;
                winner_to_triangle = distance_to_triangle;
                winner_intersection_point = triangle_intersection_point;
            }
        }

        //  now check nodes if any node is closer
        for(auto& node : nodes){
            Vector recursive_point;
            double recursive_distance = winner_to_triangle;

            Triangle* primitive = node.intersection(ray, recursive_point, recursive_distance);

            if(primitive != nullptr && recursive_distance < winner_to_triangle){
                winner = primitive;
                winner_to_triangle = recursive_distance;
                winner_intersection_point = recursive_point;
            }
        }
    }

    if(winner != nullptr){
        point = winner_intersection_point;
        distance = winner_to_triangle;
    }

    return winner;
}


// https://gamedev.stackexchange.com/questions/18436
bool OctTreeNode::intersection(const Ray& ray, double& distance) const{
    Vector dirfrac = 1.0 / ray.getDirection();
    const Vector& origin = ray.getOrigin();
    const Vector& min = aabb.get_min();
    const Vector& max = aabb.get_max();

    double t1 = (min.x - origin.x) * dirfrac.x;
    double t2 = (max.x - origin.x) * dirfrac.x;
    double t3 = (min.y - origin.y) * dirfrac.y;
    double t4 = (max.y - origin.y) * dirfrac.y;
    double t5 = (min.z - origin.z) * dirfrac.z;
    double t6 = (max.z - origin.z) * dirfrac.z;

    double tmin = std::max(
        std::max(std::min(t1, t2), std::min(t3, t4)),
        std::min(t5, t6));
    double tmax = std::min(
        std::min(std::max(t1, t2), std::max(t3, t4)),
        std::max(t5, t6));

    // If tmax is less than zero, ray (line) is intersecting AABB, but the whole
    // AABB is behind the ray.
    if (tmax < 0) {
        return false;
    }

    // If tmin is greater than tmax, ray doesn't intersect AABB.
    if (tmin > tmax) {
        return false;
    }

    distance = tmin;

    return true;
}

void OctTreeNode::split(){
    if(primitives.size() < tree::MAX_NUMER_OF_ELEMENTS){
        return;
    }

    for(auto& elem: aabb.split_to_octet() ){
        nodes.push_back({elem});
    }

    std::vector<Triangle*> remaining;

    for(Triangle* triangle: primitives){
        bool added = false;
        AABB box = triangle->make_box();

        for(auto& node: nodes){
            if(node.aabb.fully_contains(box)){
                node.primitives.push_back(triangle);
                added = true;
                break;
            }
        }

        if(!added){
            remaining.push_back(triangle);
        }
    }

    primitives = remaining;

    for(auto& node: nodes){
        node.split();
    }
}

}
