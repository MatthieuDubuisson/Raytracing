#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable{
    public:
        Sphere(){}
        Sphere(point3 cen, double r) : center(cen), radius(r) {};

        virtual bool hit(
            const Ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
    point3 center;
    double radius;      
};

// fct that return something when a ray intersect with a virtual sphere
bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    Vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());   //use dot product
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root){
        root = (-half_b + sqrtd) / a;
        if  (root < t_min || t_max < root){
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}

#endif