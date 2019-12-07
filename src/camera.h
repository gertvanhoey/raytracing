#ifndef CAMERA_H
#define CAMERA_H

#include "raytracing_export.h"
#include "ray.h"

class RAYTRACING_EXPORT Camera
{
public:
    Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 viewUp,
           double fieldOfViewVerticalDegrees, double aspectRatio,
           double aperture, double focusDistance);

    Ray get_ray(double u, double v) const;

private:
    Vec3 m_origin;
    Vec3 m_lower_left_corner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
    Vec3 m_u;
    Vec3 m_v;
    Vec3 m_w;
    double m_lensRadius;

};

#endif // CAMERA_H
