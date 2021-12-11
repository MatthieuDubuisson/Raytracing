#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class Ray
{
    // class that creates virtual rays that allow to draw on the screen : shapes, colors, light, reflexion, ... 
    public :
        Ray(){}
        Ray(const point3& origin, const Vec3& direction)
            : orig(origin), dir(direction)
            {}
        //init an origin and a direction of the ray
        point3 origin() const {return orig; }
        Vec3 direction() const {return dir; }

        //init the vector of the ray
        point3 at(double t) const{
            return orig + t*dir;
        }

    public:
        point3 orig;
        Vec3 dir;
};

#endif