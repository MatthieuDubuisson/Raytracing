#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h" 

//  generic object that the ray can intersect with
struct hit_record{
    point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    //return face of hittable object with dot product
    inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Hittable{
    public:
    virtual bool hit(const Ray&r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif