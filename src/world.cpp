#include "world.h"
#include "objectcollection.h"
#include "sphere.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "random.h"

std::unique_ptr<Object> World::randomScene()
{
    auto world = std::make_unique<ObjectCollection>();
    auto diffuseGray = std::make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5));
    world->add(std::make_unique<Sphere>(Vec3(0.0, -1000.0, 0.0), 1000.0, diffuseGray));
    auto glass = std::make_shared<Dielectric>(1.5);
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            const double chooseMat = random_double();
            Vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
            if ((center - Vec3(4.0, 0.2, 0.0)).length() > 0.9) {
                if (chooseMat < 0.8) { // diffuse
                    const Vec3 albedo(random_double() * random_double(),
                                      random_double() * random_double(),
                                      random_double() * random_double());
                    auto material = std::make_shared<Lambertian>(albedo);
                    world->add(std::make_unique<Sphere>(center, 0.2, material));
                }
                else if (chooseMat < 0.95) { // metal
                    const Vec3 albedo(0.5 * (1.0 + random_double()),
                                      0.5 * (1.0 + random_double()),
                                      0.5 * (1.0 + random_double()));
                    auto material = std::make_shared<Metal>(albedo, 0.5 * random_double());
                    world->add(std::make_unique<Sphere>(center, 0.2, material));
                }
                else { // glass
                    world->add(std::make_unique<Sphere>(center, 0.2, glass));
                }
            }
        }
    }

    auto diffuse = std::make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1));
    auto metal = std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0);
    world->add(std::make_unique<Sphere>(Vec3(0.0, 1.0, 0.0), 1.0, glass));
    world->add(std::make_unique<Sphere>(Vec3(-4.0, 1.0, 0.0), 1.0, diffuse));
    world->add(std::make_unique<Sphere>(Vec3(4.0, 1.0, 0.0), 1.0, metal));

    return std::move(world);
}
