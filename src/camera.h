#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera
{
public:
    Camera() = default;

    Ray get_ray(double u, double v) const;

private:
    Vec3 m_origin {0.0, 0.0, 0.0};
    Vec3 m_lower_left_corner {-2.0, -1.0, -1.0};
    Vec3 m_horizontal {4.0, 0.0, 0.0};
    Vec3 m_vertical {0.0, 2.0, 0.0};
};

#endif // CAMERA_H
