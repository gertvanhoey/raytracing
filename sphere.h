#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class Sphere : public Object
{
public:
    Sphere() = default;
    Sphere(Vector3D cen, double r) : m_center(cen), m_radius(r) {}

    std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const override;

private:
    Vector3D m_center {0.0, 0.0, 0.0};
    double m_radius {0.0};
};

std::optional<HitRecord> Sphere::hit(const Ray& r, double t_min, double t_max) const
{
    Vector3D oc = r.origin() - m_center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - m_radius * m_radius;
    double discriminant = b * b - a * c;
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

#endif // SPHERE_H
