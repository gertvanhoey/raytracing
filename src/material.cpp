#include "material.h"

Vec3 Material::reflect(const Vec3& v, const Vec3& n) {
    return v - 2.0 * dot(v, n) * n;
}

std::optional<Vec3> Material::refract(const Vec3& v, const Vec3& n, double ni_over_nt) {
    Vec3 uv = unit_vector(v);
    double dt = dot(uv, n);
    double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
    std::optional<Vec3> result = std::nullopt;
    if (discriminant > 0.0) {
        result = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
    }
    return result;
}

