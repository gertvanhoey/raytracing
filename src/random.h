#ifndef RANDOM_H
#define RANDOM_H

#include "vec3.h"
//#include <functional>
//#include <random>
#include <cstdlib>

//inline double random_double() {
//    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//    static std::mt19937 generator;
//    static std::function<double()> rand_generator = std::bind(distribution, generator);
//    return rand_generator();
//}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline Vec3 random_in_unit_sphere() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(random_double(), random_double(), random_double()) - Vec3(1.0, 1.0, 1.0);
    } while (p.squared_length() >= 1.0);
    return p;
}

inline Vec3 random_in_unit_disk() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(random_double(), random_double(), 0.0) - Vec3(1.0, 1.0, 0.0);
    } while (dot(p, p) >= 1.0);
    return p;
}

#endif // RANDOM_H
