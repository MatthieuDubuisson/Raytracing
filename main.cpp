#include <iostream>
#include <fstream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

color ray_color(const Ray& r){
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

// Image
std::ofstream output;
output.open("output.ppm");

const auto aspect_ratio = 16.0 / 9.0;
const int picture_width = 400;
const int picture_height = static_cast<int>(picture_width / aspect_ratio);

// Camera

auto viewport_height = 2.0;
auto viewport_width = aspect_ratio * viewport_height;
auto focal_length = 1.0;

auto origin = point3(0, 0, 0);
auto horizontal = Vec3(viewport_width, 0, 0);
auto vertical = Vec3(0, viewport_height, 0);
auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);


// Render

output << "P3\n" << picture_width << ' ' << picture_height << "\n255\n";

//rows are written out from top to bottom.
for(int j = picture_height - 1; j >= 0; --j){

    //The pixels are written out in rows with pixels left to right.
    for(int i = 0; i < picture_width; ++i){
        auto u = double(i) / (picture_width - 1);
        auto v = double(j) / (picture_height - 1);
        Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        //each of the red/green/blue components range from 0.0 to 1.0
        color pixel_color = ray_color(r);
        //variation colors
        write_color(output, pixel_color);


        //output << ir << ' ' << ig << ' ' << ib << '\n';
    }
}

output.close();
return 0;
}