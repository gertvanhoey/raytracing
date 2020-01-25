#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "raytracing_export.h"

class RAYTRACING_EXPORT Lambertian : public Material
{
public:
    Lambertian(const Vec3& albedo);

    std::optional<Ray> scatter(const Ray& ray, const HitRecord& record) const override;

private:
    Vec3 m_albedo;
};

#endif  // LAMBERTIAN_H
