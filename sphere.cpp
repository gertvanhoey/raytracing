#include "sphere.h"

std::optional<HitRecord> Sphere::hit(const Ray& r, double t_min, double t_max) const
{
    Vector3D oc = r.origin() - m_center;
    const auto a = dot(r.direction(), r.direction());
    const auto b = dot(oc, r.direction());
    const auto c = dot(oc, oc) - m_radius * m_radius;
    const auto discriminant = b * b - a * c;
    if (discriminant > 0.0) {
        double temp = (-b - sqrt(discriminant)) / a;
        if (t_min < temp && temp < t_max) {
            HitRecord record;
            record.t = temp;
            record.p = r.point_at_parameter(record.t);
            record.normal = (record.p - m_center) / m_radius;
            return record;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (t_min < temp && temp < t_max) {
            HitRecord record;
            record.t = temp;
            record.p = r.point_at_parameter(record.t);
            record.normal = (record.p - m_center) / m_radius;
            return record;
        }
    }
    return std::nullopt;
}
