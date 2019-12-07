#define _USE_MATH_DEFINES
#include <cmath>
#include "camera.h"
#include "random.h"

Camera::Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 viewUp,
               double fieldOfViewVerticalDegrees, double aspectRatio,
               double aperture, double focusDistance)
{
    m_lensRadius = aperture / 2.0;
    const double theta = fieldOfViewVerticalDegrees * M_PI / 180.0;
    const double halfHeight = tan(theta / 2.0);
    const double halfWidth = aspectRatio * halfHeight;
    m_origin = lookFrom;
    m_w = unit_vector(lookFrom - lookAt);
    m_u = unit_vector(cross(viewUp, m_w));
    m_v = cross(m_w, m_u);
    m_lower_left_corner = m_origin
                          - halfWidth * focusDistance * m_u
                          - halfHeight * focusDistance * m_v
                          - focusDistance * m_w;
    m_horizontal = 2.0 * halfWidth * focusDistance * m_u;
    m_vertical = 2.0 * halfHeight * focusDistance * m_v;
}

Ray Camera::get_ray(double s, double t) const
{
    const Vec3 rd = m_lensRadius * random_in_unit_disk();
    const Vec3 offset = m_u * rd.x() + m_v * rd.y();
    return Ray(m_origin + offset,
               m_lower_left_corner + (s * m_horizontal) + (t * m_vertical) - m_origin - offset,
               Vec3(1.0, 1.0, 1.0));
}
