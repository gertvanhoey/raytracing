#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
public:
    Ray() = default;
    Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }

    Vec3 origin() const { return A; }
    Vec3 direction() const { return B; }
    Vec3 point_at_parameter(double t) const { return A + t * B; }

    Vec3 A = {0.0, 0.0, 0.0};
    Vec3 B = {1.0, 0.0, 0.0};
};

#endif // RAY_H
