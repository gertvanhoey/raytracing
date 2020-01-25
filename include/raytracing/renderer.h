#ifndef RENDERER_H
#define RENDERER_H

#include "array2d.h"
#include "raytracing_export.h"
#include "vec3.h"

class Object;
class Camera;
class Ray;

class RAYTRACING_EXPORT Renderer
{
public:
    Renderer(size_t width, size_t height);

    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void setSize(size_t width, size_t height);
    void reset();

    Array2D<Vec3> renderIncremental(const Object& object, const Camera& camera, int numRaysPerPixel);

    static Array2D<Vec3> render(
        const Object& object, const Camera& camera, size_t width, size_t height, int numRaysPerPixel);
    static Array2D<Vec3> renderParallel(
        const Object& object, const Camera& camera, size_t width, size_t height, int numRaysPerPixel, int numThreads);

private:
    static void renderLine(const Object& object,
                           const Camera& camera,
                           size_t width,
                           size_t height,
                           size_t line,
                           int numRaysPerPixel,
                           Array2D<Vec3>& pixels);
    static Vec3 color(const Ray& r, const Object& world, int depth, int* numBounces = nullptr);

private:
    class Impl;
    Impl* m_pimpl;
};

#endif  // RENDERER_H
