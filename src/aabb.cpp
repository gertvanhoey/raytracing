#include "aabb.h"
#include "ray.h"
#include <algorithm>

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vec3 &min, const Vec3 &max) :
    m_min(min),
    m_max(max)
{
}

Vec3 AxisAlignedBoundingBox::min() const
{
    return m_min;
}

Vec3 AxisAlignedBoundingBox::max() const
{
    return m_max;
}

bool AxisAlignedBoundingBox::hit(const Ray& r, double tmin, double tmax) const
{
    for (int a = 0; a < 3; a++) {
        double invD = 1.0 / r.direction()[a];
        double t0 = (m_min[a] - r.origin()[a]) * invD;
        double t1 = (m_max[a] - r.origin()[a]) * invD;
        if (invD < 0.0) {
            std::swap(t0, t1);
        }
        tmin = (t0 > tmin) ? t0 : tmin;
        tmax = (t1 < tmax) ? t1 : tmax;
        if (tmax <= tmin) {
            return false;
        }
    }
    return true;
}

AxisAlignedBoundingBox AxisAlignedBoundingBox::surroundingBox(const AxisAlignedBoundingBox& box1,
                                                              const AxisAlignedBoundingBox& box2)
{
    Vec3 small(std::min(box1.min().x(), box2.min().x()),
               std::min(box1.min().y(), box2.min().y()),
               std::min(box1.min().z(), box2.min().z()));
    Vec3 big(std::max(box1.max().x(), box2.max().x()),
             std::max(box1.max().y(), box2.max().y()),
             std::max(box1.max().z(), box2.max().z()));
    return AxisAlignedBoundingBox(small, big);
}
