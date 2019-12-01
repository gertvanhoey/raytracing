#include "float.h"
#include "objectcollection.h"
#include "sphere.h"
#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <fstream>

void save_to_ppm(const std::string& filename, const std::vector<Vec3>& pixels, int width, int height) {
    (void)pixels;
    std::ofstream output;
    output.open(filename);
    output << "P3\n" << width << " " << height << "\n255\n";
    for (const auto& pixel : pixels) {
        output << int(pixel.r()) << " " << int(pixel.g()) << " " << int(pixel.b()) << "\n";
    }
    output.close();
}

Vec3 color(const Ray& r, const Object& world) {
    auto rec = world.hit(r, 0.0, std::numeric_limits<double>::max());
    if (rec) {
        auto normal = rec->normal;
        return 0.5 * Vec3(normal.x() + 1.0, normal.y() + 1.0, normal.z() + 1.0);
    }
    else {
        Vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    const int width = 200;
    const int height = 100;

    Vec3 lower_left_corner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);

    std::vector<std::unique_ptr<Object>> list;

    auto world = std::make_unique<ObjectCollection>();
    world->add(std::make_unique<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5));
    world->add(std::make_unique<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0));

    std::vector<Vec3> pixels(width * height);
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            double u = double(i) / double(width);
            double v = double(j) / double(height);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);

            Vec3 col = color(r, *world);

            pixels[size_t(i + (height - j - 1) * width)] = Vec3(255.99 * col.r(), 255.99 * col.g(), 255.99 * col.b());
        }
    }

    save_to_ppm("image.ppm", pixels, width, height);

    return 0;
}
