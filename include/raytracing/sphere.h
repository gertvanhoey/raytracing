#ifndef SPHERE_H
#define SPHERE_H

#include "raytracing_export.h"
#include "object.h"
#include <memory>

class Material;

class RAYTRACING_EXPORT Sphere : public Object
{
public:
    Sphere();
    Sphere(Vec3 center, double r, std::shared_ptr<Material> material);
    ~Sphere() override;

    std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const override;
    std::optional<AxisAlignedBoundingBox> boundingBox() const override;

private:
    class Impl;
    Impl* m_pimpl;
};

#endif // SPHERE_H
