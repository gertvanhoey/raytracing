#include "objectcollection.h"

void ObjectCollection::add(std::unique_ptr<Object> object)
{
    m_objects.push_back(std::move(object));
}

std::optional<HitRecord> ObjectCollection::hit(const Ray& r, double t_min, double t_max) const
{
    std::optional<HitRecord> result;
    double closest_so_far = t_max;
    for (const auto& object : m_objects) {
        auto record = object->hit(r, t_min, closest_so_far);
        if (record) {
            closest_so_far = record->t;
            result = record;
        }
    }
    return result;
}
