#include "metal.h"
#include "random.h"
#include <algorithm>

Metal::Metal(const Vec3 &albedo, double fuzziness) :
    m_albedo(albedo),
    m_fuzziness(std::min(fuzziness, 1.0))
{
}

std::optional<Ray> Metal::scatter(const Ray& ray, const HitRecord& record) const
{
    Vec3 reflected = reflect(unit_vector(ray.direction()), record.normal);
    Ray scattered(record.p, reflected + m_fuzziness * random_in_unit_sphere(), ray.color * m_albedo);
    return (dot(scattered.direction(), record.normal) > 0.0) ? std::optional<Ray>(scattered) : std::nullopt;
}

Vec3 Metal::reflect(const Vec3& v, const Vec3& n) const
{
    return v - 2.0 * dot(v, n) * n;
}
