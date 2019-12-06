#include "lambertian.h"
#include "random.h"

Lambertian::Lambertian(const Vec3& albedo) :
    m_albedo(albedo)
{
}

std::optional<Ray> Lambertian::scatter(const Ray &ray, const HitRecord &record) const
{
    Vec3 target = record.p + record.normal + random_in_unit_sphere();
    Ray scattered(record.p, target - record.p, ray.color * m_albedo);
    return scattered;
}


