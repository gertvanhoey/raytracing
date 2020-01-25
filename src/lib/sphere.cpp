#include "sphere.h"

class Sphere::Impl
{
public:
    Impl() = default;
    Impl(Vec3 center, double r, std::shared_ptr<Material> material);

    Vec3 m_center {0.0, 0.0, 0.0};
    double m_radius {0.0};
    std::shared_ptr<Material> m_material {nullptr};
};

Sphere::Impl::Impl(Vec3 center, double r, std::shared_ptr<Material> material) :
    m_center(center), m_radius(r), m_material(std::move(material))
{
}

Sphere::Sphere() : m_pimpl(new Impl) {}

Sphere::Sphere(Vec3 center, double r, std::shared_ptr<Material> material) :
    m_pimpl(new Impl(center, r, std::move(material)))
{
}

Sphere::~Sphere()
{
    delete m_pimpl;
}

std::optional<HitRecord> Sphere::hit(const Ray& r, double t_min, double t_max) const
{
    const auto center = m_pimpl->m_center;
    const auto radius = m_pimpl->m_radius;
    Vec3 oc = r.origin() - center;
    const auto a = dot(r.direction(), r.direction());
    const auto b = dot(oc, r.direction());
    const auto c = dot(oc, oc) - radius * radius;
    const auto discriminant = b * b - a * c;
    if (discriminant > 0.0) {
        double temp = (-b - sqrt(discriminant)) / a;
        if (t_min < temp && temp < t_max) {
            HitRecord record;
            record.t = temp;
            record.p = r.pointAtParameter(record.t);
            record.normal = (record.p - center) / radius;
            record.material = m_pimpl->m_material.get();
            return record;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (t_min < temp && temp < t_max) {
            HitRecord record;
            record.t = temp;
            record.p = r.pointAtParameter(record.t);
            record.normal = (record.p - center) / radius;
            record.material = m_pimpl->m_material.get();
            return record;
        }
    }
    return std::nullopt;
}

std::optional<AxisAlignedBoundingBox> Sphere::boundingBox() const
{
    const double radius = m_pimpl->m_radius;
    return AxisAlignedBoundingBox(m_pimpl->m_center - Vec3(radius, radius, radius),
                                  m_pimpl->m_center + Vec3(radius, radius, radius));
}
