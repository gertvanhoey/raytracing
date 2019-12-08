#ifndef WORLD_H
#define WORLD_H

#include "raytracing_export.h"
#include "object.h"
#include <memory>

class RAYTRACING_EXPORT World
{
public:
    World() = delete;

    static std::unique_ptr<Object> randomScene();
};

#endif // WORLD_H
