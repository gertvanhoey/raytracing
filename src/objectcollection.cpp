#include "objectcollection.h"

class ObjectCollection::Impl
{
public:
    std::vector<std::unique_ptr<Object>> m_objects;
};

ObjectCollection::ObjectCollection() : m_pimpl(new Impl)
{
}

ObjectCollection::~ObjectCollection()
{
    delete m_pimpl;
}

void ObjectCollection::add(std::unique_ptr<Object> object)
{
    m_pimpl->m_objects.push_back(std::move(object));
}

std::optional<HitRecord> ObjectCollection::hit(const Ray& r, double t_min, double t_max) const
{
    std::optional<HitRecord> result;
    double closest_so_far = t_max;
    for (const auto& object : m_pimpl->m_objects) {
        auto record = object->hit(r, t_min, closest_so_far);
        if (record) {
            closest_so_far = record->t;
            result = record;
        }
    }
    return result;
}
