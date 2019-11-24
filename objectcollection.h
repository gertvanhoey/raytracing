#ifndef OBJECT_COLLECTION_H
#define OBJECT_COLLECTION_H

#include "object.h"
#include <vector>
#include <memory>

class ObjectCollection : public Object
{
public:
    void add(std::unique_ptr<Object> l);

    std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const override;

private:
    std::vector<std::unique_ptr<Object>> m_objects;
};

void ObjectCollection::add(std::unique_ptr<Object> l)
{
    m_objects.push_back(std::move(l));
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

#endif // OBJECT_COLLECTION_H
