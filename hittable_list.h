#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>
#include <memory>

class hittable_list : public hittable
{
public:
    hittable_list() {}

    void add(std::unique_ptr<hittable> l);

    virtual std::optional<hit_record> hit(const ray& r, double t_min, double t_max) const;

    std::vector<std::unique_ptr<hittable>> list;
};

void hittable_list::add(std::unique_ptr<hittable> l)
{
    list.push_back(std::move(l));
}

std::optional<hit_record> hittable_list::hit(const ray& r, double t_min, double t_max) const
{
    std::optional<hit_record> rec;
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

#endif // HITTABLE_LIST_H
