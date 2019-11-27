#ifndef SPHERE_H
#define SPHERE_H

#include "raytracing_export.h"
#include "object.h"

class RAYTRACING_EXPORT Sphere : public Object
{
public:
    Sphere() = default;
    Sphere(Vector3D cen, double r) : m_center(cen), m_radius(r) {}

    std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const override;

private:
    Vector3D m_center {0.0, 0.0, 0.0};
    double m_radius {0.0};
};

#endif // SPHERE_H
