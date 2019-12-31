#ifndef WORLD_H
#define WORLD_H

#include "raytracing_export.h"
#include "object.h"
#include <memory>
#include <vector>

class RAYTRACING_EXPORT World
{
public:
    World() = delete;

    static std::unique_ptr<Object> randomSceneCollection();
    static std::unique_ptr<Object> randomSceneHierarchy();

private:
    static std::vector<std::unique_ptr<Object>> randomSceneVector();
};

#endif // WORLD_H
