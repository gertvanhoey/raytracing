#include "objectcollection.h"

class ObjectCollection::Impl
{
public:
    std::vector<std::unique_ptr<Object>> m_objects;
};

ObjectCollection::ObjectCollection() : m_pimpl(new Impl) {}

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
    double closestSoFar = t_max;
    for (const auto& object : m_pimpl->m_objects) {
        auto record = object->hit(r, t_min, closestSoFar);
        if (record) {
            closestSoFar = record->t;
            result = record;
        }
    }
    return result;
}

std::optional<AxisAlignedBoundingBox> ObjectCollection::boundingBox() const
{
    if (m_pimpl->m_objects.empty()) {
        return std::nullopt;
    }

    auto result = m_pimpl->m_objects[0]->boundingBox();
    if (result) {
        for (size_t i = 1; i < m_pimpl->m_objects.size(); i++) {
            auto box = m_pimpl->m_objects[i]->boundingBox();
            if (box) {
                result = AxisAlignedBoundingBox::surroundingBox(*result, *box);
            }
            else {
                result = std::nullopt;
                break;
            }
        }
    }
    return result;
}
