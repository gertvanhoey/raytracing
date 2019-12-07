#ifndef CAMERA_H
#define CAMERA_H

#include "raytracing_export.h"
#include "ray.h"

class RAYTRACING_EXPORT Camera
{
public:
    Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 viewUp, double fieldOfViewVerticalDegrees, double aspectRatio);

    Ray get_ray(double u, double v) const;

private:
    Vec3 m_origin {0.0, 0.0, 0.0};
    Vec3 m_lower_left_corner {-2.0, -1.0, -1.0};
    Vec3 m_horizontal {4.0, 0.0, 0.0};
    Vec3 m_vertical {0.0, 2.0, 0.0};
};

#endif // CAMERA_H
