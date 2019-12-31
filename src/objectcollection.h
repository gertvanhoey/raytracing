#ifndef OBJECT_COLLECTION_H
#define OBJECT_COLLECTION_H

#include "raytracing_export.h"
#include "object.h"
#include "aabb.h"
#include <vector>
#include <memory>
#include <optional>

class RAYTRACING_EXPORT ObjectCollection : public Object
{
public:
    ObjectCollection();
    ~ObjectCollection() override;

    ObjectCollection(const ObjectCollection&) = delete;
    ObjectCollection& operator=(const ObjectCollection&) = delete;
    ObjectCollection(ObjectCollection&&) = delete;
    ObjectCollection& operator=(ObjectCollection&&) = delete;

    void add(std::unique_ptr<Object> l);
    std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const override;
    std::optional<AxisAlignedBoundingBox> boundingBox() const override;

private:
    class Impl;
    Impl* m_pimpl;
};

#endif // OBJECT_COLLECTION_H
