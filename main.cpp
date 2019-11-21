#include "float.h"
#include "hittable_list.h"
#include "sphere.h"
#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <fstream>

void save_to_ppm(const std::string& filename, const std::vector<vec3>& pixels, int width, int height) {
    (void)pixels;
    std::ofstream output;
    output.open(filename);
    output << "P3\n" << width << " " << height << "\n255\n";
    for (const auto& pixel : pixels) {
        output << int(pixel.r()) << " " << int(pixel.g()) << " " << int(pixel.b()) << "\n";
    }
    output.close();
}

vec3 color(const ray& r, hittable *world) {
    auto rec = world->hit(r, 0.0, std::numeric_limits<double>::max());
    if (rec) {
        auto normal = (*rec).normal;
        return 0.5 * vec3(normal.x() + 1.0, normal.y() + 1.0, normal.z() + 1.0);
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    const int width = 200;
    const int height = 100;

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hittable *list[2];
    list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
    list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0);
    hittable *world = new hittable_list(list, 2);

    std::vector<vec3> pixels(width * height);
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            double u = double(i) / double(width);
            double v = double(j) / double(height);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);

            vec3 col = color(r, world);

            pixels[size_t(i + (height - j - 1) * width)] = vec3(255.99 * col.r(), 255.99 * col.g(), 255.99 * col.b());
        }
    }

    save_to_ppm("image.ppm", pixels, width, height);

    return 0;
}
