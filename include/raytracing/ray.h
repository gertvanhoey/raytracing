#ifndef RAY_H
#define RAY_H

#include "raytracing_export.h"
#include "vec3.h"

class RAYTRACING_EXPORT Ray
{
public:
    Ray() = default;
    Ray(const Vec3& a, const Vec3& b, const Vec3& c)
    {
        A = a;
        B = b;
        color = c;
    }

    Vec3 origin() const { return A; }
    Vec3 direction() const { return B; }
    Vec3 pointAtParameter(double t) const { return A + t * B; }

    Vec3 A {0.0, 0.0, 0.0};
    Vec3 B {1.0, 0.0, 0.0};
    Vec3 color {1.0, 1.0, 1.0};
};

#endif  // RAY_H
