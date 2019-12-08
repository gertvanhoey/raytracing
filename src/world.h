#ifndef WORLD_H
#define WORLD_H

#include "object.h"
#include <memory>

class World
{
public:
    World() = delete;

    static std::unique_ptr<Object> randomScene();
};

#endif // WORLD_H
