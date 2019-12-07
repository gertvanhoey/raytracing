#define _USE_MATH_DEFINES
#include <cmath>
#include <cfloat>
#include "objectcollection.h"
#include "sphere.h"
#include "camera.h"
#include "random.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
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

Vec3 color(const Ray& r, const Object& world, int depth) {
    auto rec = world.hit(r, 0.001, std::numeric_limits<double>::max());
    Vec3 result;
    if (rec) {
        if (depth < 50) {
            auto scattered = rec->material->scatter(r, *rec);
            if (scattered) {
                result = color(*scattered, world, depth + 1);
            }
            else {
                result = Vec3(0.0, 0.0, 0.0);
            }
        }
        else {
            result = Vec3(0.0, 0.0, 0.0);
        }
    }
    else {
        Vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        result = r.color * ((1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0));
    }
    return result;
}

int main() {
    const int width = 200;
    const int height = 100;
    const int numSamples = 100;

    Vec3 lower_left_corner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);

    std::vector<std::unique_ptr<Object>> list;

    auto lambertian1 = std::make_shared<Lambertian>(Vec3(0.1, 0.2, 0.5));
    auto lambertian2 = std::make_shared<Lambertian>(Vec3(0.8, 0.8, 0.0));
    auto metal = std::make_shared<Metal>(Vec3(0.8, 0.6, 0.2), 0.0);
    auto dielectric = std::make_shared<Dielectric>(1.5);

    auto world = std::make_unique<ObjectCollection>();
    world->add(std::make_unique<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5, lambertian1));
    world->add(std::make_unique<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0, lambertian2));
    world->add(std::make_unique<Sphere>(Vec3(1.0, 0.0, -1.0), 0.5, metal));
    world->add(std::make_unique<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.5, dielectric));
    world->add(std::make_unique<Sphere>(Vec3(-1.0, 0.0, -1.0), -0.45, dielectric));

//    const double R = cos(M_PI / 4.0);
//    auto world = std::make_unique<ObjectCollection>();
//    world->add(std::make_unique<Sphere>(Vec3(-R, 0.0, -1.0), R, std::make_shared<Lambertian>(Vec3(0.0, 0.0, 1.0))));
//    world->add(std::make_unique<Sphere>(Vec3(R, 0.0, -1.0), R, std::make_shared<Lambertian>(Vec3(1.0, 0.0, 0.0))));

    Camera camera(Vec3(-2.0, 2.0, 1.0), Vec3(0.0, 0.0, -1.0), Vec3(0.0, 1.0, 0.0), 20.0, double(width) / double(height));

    std::vector<Vec3> pixels(width * height);
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            Vec3 pixel(0.0, 0.0, 0.0);
            for (int s = 0; s < numSamples; s++) {
                const double u = (double(i) + random_double()) / double(width);
                const double v = (double(j) + random_double()) / double(height);
                const Ray r = camera.get_ray(u, v);
                pixel += color(r, *world, 0);
            }
            pixel /= double(numSamples);
            pixel = Vec3(sqrt(pixel[0]), sqrt(pixel[1]), sqrt(pixel[2]));
            pixels[i + (height - j - 1) * width] = Vec3(255.99 * pixel.r(), 255.99 * pixel.g(), 255.99 * pixel.b());
        }
    }

    save_to_ppm("image.ppm", pixels, width, height);

    return 0;
}
