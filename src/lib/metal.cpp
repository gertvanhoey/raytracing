#include "metal.h"

#include <algorithm>

#include "random.h"

Metal::Metal(const Vec3& albedo, double fuzziness) : m_albedo(albedo), m_fuzziness(std::min(fuzziness, 1.0)) {}

std::optional<Ray> Metal::scatter(const Ray& ray, const HitRecord& record) const
{
    Vec3 reflected = reflect(unitVector(ray.direction()), record.normal);
    Ray scattered(record.p, reflected + m_fuzziness * randomInUnitSphere(), ray.color * m_albedo);
    return (dot(scattered.direction(), record.normal) > 0.0) ? std::optional<Ray>(scattered) : std::nullopt;
}
