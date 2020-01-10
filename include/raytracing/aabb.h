#ifndef AABB_H
#define AABB_H

#include "raytracing_export.h"
#include "vec3.h"

class Ray;

class RAYTRACING_EXPORT AxisAlignedBoundingBox
{
public:
    AxisAlignedBoundingBox() = default;
    AxisAlignedBoundingBox(const Vec3& min, const Vec3& max);

    Vec3 min() const;
    Vec3 max() const;

    bool hit(const Ray& r, double tmin, double tmax) const;

    static AxisAlignedBoundingBox surroundingBox(const AxisAlignedBoundingBox& box1,
                                                 const AxisAlignedBoundingBox& box2);
private:
    Vec3 m_min {0.0, 0.0, 0.0};
    Vec3 m_max {0.0, 0.0, 0.0};
};

#endif // AABB_H
