#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"
#include <optional>

struct HitRecord {
    double t;
    Vector3D p;
    Vector3D normal;
};

class Object {
public:
    virtual std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const = 0;
};

#endif // OBJECT_H
