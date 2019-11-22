#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
public:
    Ray() {}
    Ray(const Vector3D &a, const Vector3D &b) { A = a; B = b; }

    Vector3D origin() const { return A; }
    Vector3D direction() const { return B; }
    Vector3D point_at_parameter(double t) const { return A + t * B; }

    Vector3D A = {0.0, 0.0, 0.0};
    Vector3D B = {1.0, 0.0, 0.0};
};

#endif // RAY_H
