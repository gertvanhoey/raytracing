#ifndef OBJECT_H
#define OBJECT_H

#include <optional>

#include "aabb.h"
#include "ray.h"
#include "raytracing_export.h"

class Material;

struct RAYTRACING_EXPORT HitRecord
{
    double t {0.0};
    Vec3 p {0.0, 0.0, 0.0};
    Vec3 normal {1.0, 0.0, 0.0};
    Material* material {nullptr};
};

class RAYTRACING_EXPORT Object
{
public:
    Object() = default;
    virtual ~Object() = default;
    Object(const Object&) = default;
    Object& operator=(const Object&) = default;
    Object(Object&&) = default;
    Object& operator=(Object&&) = default;

    virtual std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const = 0;
    virtual std::optional<AxisAlignedBoundingBox> boundingBox() const = 0;
};

#endif  // OBJECT_H
