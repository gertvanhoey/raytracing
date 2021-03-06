#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "raytracing_export.h"

class RAYTRACING_EXPORT Metal : public Material
{
public:
    Metal(const Vec3& albedo, double fuzziness = 0.0);

    std::optional<Ray> scatter(const Ray& ray, const HitRecord& record) const override;

private:
    Vec3 m_albedo;
    double m_fuzziness;
};

#endif  // METAL_H
