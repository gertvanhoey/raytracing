#ifndef MATERIAL_H
#define MATERIAL_H

#include "raytracing_export.h"
#include "object.h"
#include <optional>

class RAYTRACING_EXPORT Material
{
public:
    Material() = default;
    virtual ~Material() = default;
    Material(const Material&) = default;
    Material& operator=(const Material&) = default;
    Material(Material&&) = default;
    Material& operator=(Material&&) = default;

    virtual std::optional<Ray> scatter(const Ray& ray, const HitRecord& record) const = 0;

    static Vec3 reflect(const Vec3& v, const Vec3& n);
    static std::optional<Vec3> refract(const Vec3& v, const Vec3& n, double ni_over_nt);
};

#endif // MATERIAL_H
