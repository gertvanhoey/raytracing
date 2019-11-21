#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <optional>

struct hit_record {
    double t;
    vec3 p;
    vec3 normal;
};

class hittable {
public:
    virtual std::optional<hit_record> hit(const ray& r, double t_min, double t_max) const = 0;
};

#endif // HITTABLE_H
