#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "object.h"
#include "raytracing_export.h"

class RAYTRACING_EXPORT World
{
public:
    World() = delete;

    static std::unique_ptr<Object> randomSceneCollection();
    static std::unique_ptr<Object> randomSceneHierarchy();

private:
    static std::vector<std::unique_ptr<Object>> randomSceneVector();
};

#endif  // WORLD_H
