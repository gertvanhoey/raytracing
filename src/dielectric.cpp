#include "dielectric.h"
#include "random.h"
#include <cmath>
#include <cassert>

Dielectric::Dielectric(double refractiveIndex) :
    m_refractiveIndex(refractiveIndex)
{
}

std::optional<Ray> Dielectric::scatter(const Ray& ray, const HitRecord& record) const
{
    Vec3 outwardNormal;
    Vec3 reflected = Material::reflect(ray.direction(), record.normal);
    double ni_over_nt;

    double reflectionProbability;
    double cosine;

    if (dot(ray.direction(), record.normal) > 0.0) {
        outwardNormal = -record.normal;
        ni_over_nt = m_refractiveIndex;
        cosine = m_refractiveIndex * dot(ray.direction(), record.normal)
                / ray.direction().length();
    }
    else {
        outwardNormal = record.normal;
        ni_over_nt = 1.0 / m_refractiveIndex;
        cosine = -dot(ray.direction(), record.normal)
                / ray.direction().length();
    }

    auto refracted = Material::refract(ray.direction(), outwardNormal, ni_over_nt);
    if (refracted) {
        reflectionProbability = schlick(cosine, m_refractiveIndex);
    }
    else {
        reflectionProbability = 1.0;
    }

    Ray scattered;
    if (random_double() < reflectionProbability) {
        scattered = Ray(record.p, reflected, ray.color); // no attenuation
    }
    else {
        assert(refracted);
        scattered = Ray(record.p, *refracted, ray.color); // no attenuation
    }
    return scattered;
}

double Dielectric::schlick(double cosine, double refractiveIndex)
{
    double r0 = (1.0 - refractiveIndex) / (1.0 + refractiveIndex);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5.0);
}
