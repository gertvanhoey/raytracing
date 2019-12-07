#define _USE_MATH_DEFINES
#include <cmath>
#include "camera.h"

Camera::Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 viewUp,
               double fieldOfViewVerticalDegrees, double aspectRatio)
{
    const double theta = fieldOfViewVerticalDegrees * M_PI / 180.0;
    const double halfHeight = tan(theta / 2.0);
    const double halfWidth = aspectRatio * halfHeight;
    m_origin = lookFrom;
    const auto w = unit_vector(lookFrom - lookAt);
    const auto u = unit_vector(cross(viewUp, w));
    const auto v = cross(w, u);
    m_lower_left_corner = m_origin - halfWidth * u - halfHeight * v - w;
    m_horizontal = 2.0 * halfWidth * u;
    m_vertical = 2.0 * halfHeight * v;
}

Ray Camera::get_ray(double u, double v) const
{
    return Ray(m_origin,
               m_lower_left_corner + (u * m_horizontal) + (v * m_vertical) - m_origin,
               Vec3(1.0, 1.0, 1.0));
}
