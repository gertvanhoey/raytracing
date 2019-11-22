#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class Sphere : public Object
{
public:
    Sphere() {}
    Sphere(Vector3D cen, double r) : center(cen), radius(r) {}

    virtual std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const;

    Vector3D center;
    double radius;
};

std::optional<HitRecord> Sphere::hit(const Ray& r, double t_min, double t_max) const
{
    Vector3D oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - a * c;
    if (discriminant > 0.0) {
        double temp = (-b - sqrt(discriminant)) / a;
        if (t_min < temp && temp < t_max) {
            HitRecord rec;
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return rec;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (t_min < temp && temp < t_max) {
            HitRecord rec;
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return rec;
        }
    }
    return std::nullopt;
}

#endif // SPHERE_H
