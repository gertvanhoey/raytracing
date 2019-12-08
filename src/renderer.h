#ifndef RENDERER_H
#define RENDERER_H

#include "raytracing_export.h"
#include "vec3.h"
#include <vector>

class Object;
class Camera;
class Ray;

class RAYTRACING_EXPORT Renderer
{
public:
    Renderer() = delete;

    static std::vector<Vec3> render(const Object& object, const Camera& camera, size_t width, size_t height, int numRaysPerPixel);

private:
    static Vec3 color(const Ray& r, const Object& world, int depth);

};

#endif // RENDERER_H
