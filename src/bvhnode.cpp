#include "bvhnode.h"
#include "random.h"
#include "aabb.h"
#include <algorithm>
#include <iostream>

class BoundingVolumeHierarchyNode::Impl
{
public:
    std::unique_ptr<Object> m_leftNode { nullptr };
    std::unique_ptr<Object> m_rightNode { nullptr };
    std::unique_ptr<Object> m_object { nullptr };
    AxisAlignedBoundingBox m_box {};
};

BoundingVolumeHierarchyNode::BoundingVolumeHierarchyNode() :
    m_pimpl(new Impl)
{
}

BoundingVolumeHierarchyNode::BoundingVolumeHierarchyNode(std::vector<std::unique_ptr<Object>>& objects) :
    m_pimpl(new Impl)
{
    initialize(objects, 0, objects.size() - 1);
}

BoundingVolumeHierarchyNode::~BoundingVolumeHierarchyNode()
{
    delete m_pimpl;
}

std::optional<HitRecord> BoundingVolumeHierarchyNode::hit(const Ray &r, double t_min, double t_max) const
{
    std::optional<HitRecord> result = std::nullopt;

    if (m_pimpl->m_box.hit(r, t_min, t_max)) {
        if (m_pimpl->m_object) {
            result = m_pimpl->m_object->hit(r, t_min, t_max);
        }
        else {
            auto leftRecord = m_pimpl->m_leftNode->hit(r, t_min, t_max);
            auto rightRecord = m_pimpl->m_rightNode->hit(r, t_min, t_max);
            if (leftRecord && rightRecord) {
                if (leftRecord->t < rightRecord->t) {
                    result = leftRecord;
                }
                else {
                    result = rightRecord;
                }
            }
            else if (leftRecord) {
                result = leftRecord;
            }
            else if (rightRecord) {
                result = rightRecord;
            }
        }
    }

    return result;
}

std::optional<AxisAlignedBoundingBox> BoundingVolumeHierarchyNode::boundingBox() const
{
    return m_pimpl->m_box;
}

BoundingVolumeHierarchyNode::BoundingVolumeHierarchyNode(std::vector<std::unique_ptr<Object>>& objects,
                                                         size_t from, size_t to) :
    m_pimpl(new Impl)
{
    initialize(objects, from, to);
}

void BoundingVolumeHierarchyNode::initialize(std::vector<std::unique_ptr<Object>>& objects,
                                             size_t from, size_t to)
{
    int axis = int(3.0 * random_double());

    auto fromIterator = objects.begin() + static_cast<long>(from);
    auto toIterator = objects.begin() + static_cast<long>(to);
    if (axis == 0) {
        std::sort(fromIterator, toIterator, [](std::unique_ptr<Object>& obj1, std::unique_ptr<Object>& obj2) {
            auto box1 = obj1->boundingBox();
            auto box2 = obj2->boundingBox();
            if (!box1 || !box2) {
                std::cerr << "No bounding box in BoundingVolumeHierarchyNode constructor" << std::endl;
            }
            return (box1->min().x() - box2->min().x() < 0.0);
        });
    }
    else if (axis == 1) {
        std::sort(fromIterator, toIterator, [](std::unique_ptr<Object>& obj1, std::unique_ptr<Object>& obj2) {
            auto box1 = obj1->boundingBox();
            auto box2 = obj2->boundingBox();
            if (!box1 || !box2) {
                std::cerr << "No bounding box in BoundingVolumeHierarchyNode constructor" << std::endl;
            }
            return (box1->min().y() - box2->min().y() < 0.0);
        });
    }
    else {
        std::sort(fromIterator, toIterator, [](std::unique_ptr<Object>& obj1, std::unique_ptr<Object>& obj2) {
            auto box1 = obj1->boundingBox();
            auto box2 = obj2->boundingBox();
            if (!box1 || !box2) {
                std::cerr << "No bounding box in BoundingVolumeHierarchyNode constructor" << std::endl;
            }
            return (box1->min().z() - box2->min().z() < 0.0);
        });
    }

    const size_t n = 1 + to - from;

    if (n == 1) {
        m_pimpl->m_object = std::move(objects[from]);

        auto box = m_pimpl->m_object->boundingBox();
        if (!box) {
            std::cerr << "No bounding box in BoundingVolumeHierarchyNode constructor" << std::endl;
        }
        else {
            m_pimpl->m_box = *box;
        }
    }
    else {
        m_pimpl->m_leftNode.reset(new BoundingVolumeHierarchyNode(objects, from, from + n / 2 - 1));
        m_pimpl->m_rightNode.reset(new BoundingVolumeHierarchyNode(objects, from + n / 2, to));

        auto leftBox = m_pimpl->m_leftNode->boundingBox();
        auto rightBox = m_pimpl->m_rightNode->boundingBox();

        if (!leftBox || !rightBox) {
            std::cerr << "No bounding box in BoundingVolumeHierarchyNode constructor" << std::endl;
        }
        else {
            m_pimpl->m_box = AxisAlignedBoundingBox::surroundingBox(*leftBox, *rightBox);
        }
    }
}
