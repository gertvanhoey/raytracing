#ifndef OBJECT_COLLECTION_H
#define OBJECT_COLLECTION_H

#include "raytracing_export.h"
#include "object.h"
#include <vector>
#include <memory>

class RAYTRACING_EXPORT ObjectCollection : public Object
{
public:
    void add(std::unique_ptr<Object> l);
    std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const override;

private:
    std::vector<std::unique_ptr<Object>> m_objects;
};


#endif // OBJECT_COLLECTION_H
