#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include <optional>

#include "material.h"
#include "raytracing_export.h"

class RAYTRACING_EXPORT Dielectric : public Material
{
public:
    Dielectric(double refractiveIndex);

    std::optional<Ray> scatter(const Ray& ray, const HitRecord& record) const override;

    static double schlick(double cosine, double refractiveIndex);

private:
    double m_refractiveIndex;
};

#endif  // DIELECTRIC_H
