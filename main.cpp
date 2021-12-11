#include <iostream>
#include <fstream>

#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "camera.h"


color ray_color(const Ray& r, const Hittable& world, int depth){
    hit_record rec;
    if (depth <=0){
        return color(0,0,0);
    }

    if(world.hit(r, 0, infinity, rec)){
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth -1);
    }
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

// Image

std::ofstream output;
output.open("output.ppm");   //open output.ppm file

const auto aspect_ratio = 16.0 / 9.0;
const int picture_width = 400;
const int picture_height = static_cast<int>(picture_width / aspect_ratio); //adapt picture height with aspect ratio and picture width
const int samples_per_pixel = 100;
const int max_depth = 50;

// World
Hittable_list world;
world.add(make_shared<Sphere>(point3(0,0,-1), 0.5));
world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));

// Camera
Camera cam;

// Render

output << "P3\n" << picture_width << ' ' << picture_height << "\n255\n";     //send picture size to the output file

//columns of pixels (top to bottom)
for(int j = picture_height - 1; j >= 0; --j){

    //rows of pixels (left to right)
    for(int i = 0; i < picture_width; ++i){
        color pixel_color(0,0,0);
        for (int s = 0; s < samples_per_pixel; ++s){
            auto u = double(i + random_double()) / (picture_width - 1);
        auto v = double(j + random_double()) / (picture_height - 1);
        Ray r = cam.get_ray(u, v);
        pixel_color +=ray_color(r, world, max_depth);
        }
        write_color(output, pixel_color, samples_per_pixel); //give colors behaviour to the output file (fct write_color in color.h)
    }
}
output.close();   //close output file
return 0;
}