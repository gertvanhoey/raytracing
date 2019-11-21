#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

class hittable_list : public hittable
{
public:
    hittable_list() {}
    hittable_list(hittable **l, int n) : list(l), list_size(n) {}

    virtual std::optional<hit_record> hit(const ray& r, double t_min, double t_max) const;

    hittable **list;
    int list_size;
};

std::optional<hit_record> hittable_list::hit(const ray& r, double t_min, double t_max) const
{
    std::optional<hit_record> rec;
    double closest_so_far = t_max;
    for (int i = 0; i < list_size; i++) {
        auto temp_rec = list[i]->hit(r, t_min, closest_so_far);
        if (temp_rec) {
            closest_so_far = (*temp_rec).t;
            rec = temp_rec;
        }
    }
    return rec;
}

#endif // HITTABLE_LIST_H
