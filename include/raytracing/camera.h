#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "raytracing_export.h"

class RAYTRACING_EXPORT Camera
{
public:
    Camera(Vec3 lookFrom,
           Vec3 lookAt,
           Vec3 viewUp,
           double fieldOfViewVerticalDegrees,
           double aspectRatio,
           double aperture,
           double focusDistance);

    Ray ray(double u, double v) const;

private:
    Vec3 m_origin;
    Vec3 m_lowerLeftCorner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
    Vec3 m_u;
    Vec3 m_v;
    Vec3 m_w;
    double m_lensRadius;
};

#endif  // CAMERA_H
