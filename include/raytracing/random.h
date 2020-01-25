#ifndef RANDOM_H
#define RANDOM_H

#include <functional>
#include <random>

#include "vec3.h"

inline double randomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    static std::function<double()> rand_generator = std::bind(distribution, generator);
    return rand_generator();
}

inline Vec3 randomInUnitSphere()
{
    Vec3 p;
    do {
        p = 2.0 * Vec3(randomDouble(), randomDouble(), randomDouble()) - Vec3(1.0, 1.0, 1.0);
    } while (p.squaredLength() >= 1.0);
    return p;
}

inline Vec3 randomInUnitDisk()
{
    Vec3 p;
    do {
        p = 2.0 * Vec3(randomDouble(), randomDouble(), 0.0) - Vec3(1.0, 1.0, 0.0);
    } while (dot(p, p) >= 1.0);
    return p;
}

#endif  // RANDOM_H
