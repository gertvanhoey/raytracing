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
};

#endif // MATERIAL_H
