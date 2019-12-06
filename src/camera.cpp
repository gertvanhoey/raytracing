#include "camera.h"

Ray Camera::get_ray(double u, double v) const
{
    return Ray(m_origin,
               m_lower_left_corner + (u * m_horizontal) + (v * m_vertical) - m_origin,
               Vec3(1.0, 1.0, 1.0));
}
