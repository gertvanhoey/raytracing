#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
public:
    sphere() {}
    sphere(vec3 cen, double r) : center(cen), radius(r) {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

    vec3 center;
    double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - a * c;
    if (discriminant > 0.0) {
        double temp = (-b - std::sqrt(discriminant)) / a;
        if (t_min < temp && temp < t_max) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + std::sqrt(discriminant)) / a;
        if (t_min < temp && temp < t_max) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif // SPHERE_H
