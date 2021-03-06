#include "world.h"

#include <vector>

#include "bvhnode.h"
#include "dielectric.h"
#include "lambertian.h"
#include "metal.h"
#include "objectcollection.h"
#include "random.h"
#include "sphere.h"

std::unique_ptr<Object> World::randomSceneCollection()
{
    auto objects = randomSceneVector();
    auto world = std::make_unique<ObjectCollection>();
    for (auto& object : objects) {
        world->add(std::move(object));
    }
    return world;
}

std::unique_ptr<Object> World::randomSceneHierarchy()
{
    auto objects = randomSceneVector();
    return std::make_unique<BoundingVolumeHierarchyNode>(objects);
}

std::vector<std::unique_ptr<Object>> World::randomSceneVector()
{
    std::vector<std::unique_ptr<Object>> objects;
    auto diffuseGray = std::make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5));
    objects.push_back(std::make_unique<Sphere>(Vec3(0.0, -1000.0, 0.0), 1000.0, diffuseGray));
    auto glass = std::make_shared<Dielectric>(1.5);
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            const double chooseMat = randomDouble();
            Vec3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());
            if ((center - Vec3(4.0, 0.2, 0.0)).length() > 0.9) {
                if (chooseMat < 0.8) {  // diffuse
                    const Vec3 albedo(randomDouble() * randomDouble(),
                                      randomDouble() * randomDouble(),
                                      randomDouble() * randomDouble());
                    auto material = std::make_shared<Lambertian>(albedo);
                    objects.push_back(std::make_unique<Sphere>(center, 0.2, material));
                }
                else if (chooseMat < 0.95) {  // metal
                    const Vec3 albedo(
                        0.5 * (1.0 + randomDouble()), 0.5 * (1.0 + randomDouble()), 0.5 * (1.0 + randomDouble()));
                    auto material = std::make_shared<Metal>(albedo, 0.5 * randomDouble());
                    objects.push_back(std::make_unique<Sphere>(center, 0.2, material));
                }
                else {  // glass
                    objects.push_back(std::make_unique<Sphere>(center, 0.2, glass));
                }
            }
        }
    }

    auto diffuse = std::make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1));
    auto metal = std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0);
    objects.push_back(std::make_unique<Sphere>(Vec3(0.0, 1.0, 0.0), 1.0, glass));
    objects.push_back(std::make_unique<Sphere>(Vec3(-4.0, 1.0, 0.0), 1.0, diffuse));
    objects.push_back(std::make_unique<Sphere>(Vec3(4.0, 1.0, 0.0), 1.0, metal));

    return objects;
}
