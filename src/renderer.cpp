#include "renderer.h"
#include "world.h"
#include "random.h"
#include "material.h"
#include "camera.h"
#include <iostream>

Array2D<Vec3> Renderer::render(const Object& object, const Camera& camera, size_t width, size_t height, int numRaysPerPixel)
{
    Array2D<Vec3> pixels(width, height);
    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < width; i++) {
            Vec3 pixel(0.0, 0.0, 0.0);
            for (int s = 0; s < numRaysPerPixel; s++) {
                const double u = (double(i) + random_double()) / double(width);
                const double v = (double(height - 1 - j) + random_double()) / double(height);
                const Ray r = camera.get_ray(u, v);
                int numBounces;
                pixel += color(r, object, 0, &numBounces);
            }
            pixel /= double(numRaysPerPixel);
            pixels(i, j) = pixel;
        }
    }
    return pixels;
}

Vec3 Renderer::color(const Ray& r, const Object& world, int depth, int* numBounces)
{
    static int staticNumBounces;

    staticNumBounces = depth + 1;

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

    if (numBounces) {
        *numBounces = staticNumBounces;
    }
    return result;
}
