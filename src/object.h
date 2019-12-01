#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"
#include <optional>

struct HitRecord {
    double t {0.0};
    Vec3 p {0.0, 0.0, 0.0};
    Vec3 normal {1.0, 0.0, 0.0};
};

class Object {
public:
    Object() = default;
    virtual ~Object() = default;
    Object(const Object&) = default;
    Object& operator=(const Object&) = default;
    Object(Object&&) = default;
    Object& operator=(Object&&) = default;

    virtual std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const = 0;
};

#endif // OBJECT_H
