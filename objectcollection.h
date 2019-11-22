#ifndef OBJECT_COLLECTION_H
#define OBJECT_COLLECTION_H

#include "object.h"
#include <vector>
#include <memory>

class ObjectCollection : public Object
{
public:
    ObjectCollection() {}

    void add(std::unique_ptr<Object> l);

    virtual std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const;

    std::vector<std::unique_ptr<Object>> list;
};

void ObjectCollection::add(std::unique_ptr<Object> l)
{
    list.push_back(std::move(l));
}

std::optional<HitRecord> ObjectCollection::hit(const Ray& r, double t_min, double t_max) const
{
    std::optional<HitRecord> rec;
    double closest_so_far = t_max;
    for (const auto& h : list) {
        auto temp_rec = h->hit(r, t_min, closest_so_far);
        if (temp_rec) {
            closest_so_far = temp_rec->t;
            rec = temp_rec;
        }
    }
    return rec;
}

#endif // OBJECT_COLLECTION_H
