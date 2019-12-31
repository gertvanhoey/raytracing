#ifndef BVHNODE_H
#define BVHNODE_H

#include "raytracing_export.h"
#include "object.h"
#include <vector>

class RAYTRACING_EXPORT BoundingVolumeHierarchyNode : public Object
{
public:
    BoundingVolumeHierarchyNode();
    BoundingVolumeHierarchyNode(std::vector<std::unique_ptr<Object>>& objects);
    ~BoundingVolumeHierarchyNode() override;

    BoundingVolumeHierarchyNode(const BoundingVolumeHierarchyNode&) = delete;
    BoundingVolumeHierarchyNode& operator=(const BoundingVolumeHierarchyNode&) = delete;
    BoundingVolumeHierarchyNode(BoundingVolumeHierarchyNode&&) = delete;
    BoundingVolumeHierarchyNode& operator=(BoundingVolumeHierarchyNode&&) = delete;

    std::optional<HitRecord> hit(const Ray& r, double t_min, double t_max) const override;
    std::optional<AxisAlignedBoundingBox> boundingBox() const override;

private:
    BoundingVolumeHierarchyNode(std::vector<std::unique_ptr<Object>>& objects,
                                size_t from, size_t to);

    void initialize(std::vector<std::unique_ptr<Object>>& objects,
                    size_t from, size_t to);

private:
    class Impl;
    Impl* m_pimpl;
};

#endif // BVHNODE_H
