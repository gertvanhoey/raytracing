#include "renderer.h"
#include "world.h"
#include "random.h"
#include "material.h"
#include "camera.h"
#include <thread>
#include <mutex>
#include <optional>
#include <vector>
#include <algorithm>

class WorkList
{
public:
    explicit WorkList(size_t numTasks) :
        m_numTasks(numTasks),
        m_nextTask(0)
    {}

    std::optional<size_t> getTask() {
        std::lock_guard<std::mutex> guard(m_mutex);
        return (m_nextTask < m_numTasks) ? std::optional<size_t>(m_nextTask++) : std::nullopt;
    }

private:
    size_t m_numTasks;
    size_t m_nextTask;
    std::mutex m_mutex;
};

class Renderer::Impl {
public:
    Impl(size_t width, size_t height);

    size_t m_width;
    size_t m_height;
    int m_numRaysPerPixel;
    Array2D<Vec3> m_pixelsCumulative;
    Array2D<Vec3> m_pixels;
};

Renderer::Impl::Impl(size_t width, size_t height) :
    m_width(width),
    m_height(height),
    m_numRaysPerPixel(0),
    m_pixelsCumulative(width, height, Vec3(0.0, 0.0, 0.0)),
    m_pixels(width, height, Vec3(0.0, 0.0, 0.0))
{
}

Renderer::Renderer(size_t width, size_t height) :
    m_pimpl(new Impl(width, height))
{
}

Renderer::~Renderer()
{
    delete m_pimpl;
}

void Renderer::setSize(size_t width, size_t height)
{
    m_pimpl->m_width = width;
    m_pimpl->m_height = height;
    m_pimpl->m_numRaysPerPixel = 0;
    m_pimpl->m_pixelsCumulative = Array2D<Vec3>(width, height, Vec3(0.0, 0.0, 0.0));
    m_pimpl->m_pixels = Array2D<Vec3>(width, height, Vec3(0.0, 0.0, 0.0));
}

void Renderer::reset()
{
    setSize(m_pimpl->m_width, m_pimpl->m_height);
}

Array2D<Vec3> Renderer::renderIncremental(const Object& object, const Camera& camera, int numRaysPerPixel)
{
    unsigned int numThreads = std::thread::hardware_concurrency();
    numThreads = std::max(numThreads, 2u);
    auto increment = renderParallel(object, camera, m_pimpl->m_width, m_pimpl->m_height, numRaysPerPixel, int(numThreads));
    m_pimpl->m_numRaysPerPixel += numRaysPerPixel;
    for (size_t row = 0; row < m_pimpl->m_height; row++) {
        for (size_t col = 0; col < m_pimpl->m_width; col++) {

            m_pimpl->m_pixelsCumulative(col, row) += (increment(col, row) * numRaysPerPixel);
            m_pimpl->m_pixels(col, row) = m_pimpl->m_pixelsCumulative(col, row) / m_pimpl->m_numRaysPerPixel;
        }
    }

    return m_pimpl->m_pixels;
}

Array2D<Vec3> Renderer::render(const Object& object, const Camera& camera, size_t width, size_t height, int numRaysPerPixel)
{
    Array2D<Vec3> pixels(width, height);
    for (size_t j = 0; j < height; j++) {
        renderLine(object, camera, width, height, j, numRaysPerPixel, pixels);
    }
    return pixels;
}

Array2D<Vec3> Renderer::renderParallel(const Object& object, const Camera& camera, size_t width, size_t height, int numRaysPerPixel, int numThreads)
{
    (void)object;
    (void)camera;
    (void)numRaysPerPixel;

    Array2D<Vec3> pixels(width, height);
    WorkList workList(height);
    std::vector<std::thread> threads;
    for (int t = 0; t < numThreads; t++) {
        threads.emplace_back([&](){
            auto workItem = workList.getTask();
            while (workItem) {
                size_t j = *workItem;
                renderLine(object, camera, width, height, j, numRaysPerPixel, pixels);
                workItem = workList.getTask();
            }
        });
    }
    for (auto& entry: threads) {
        entry.join();
    }
    return pixels;
}

void Renderer::renderLine(const Object& object, const Camera& camera, size_t width, size_t height, size_t line, int numRaysPerPixel, Array2D<Vec3>& pixels)
{
    for (size_t i = 0; i < width; i++) {
        Vec3 pixel(0.0, 0.0, 0.0);
        for (int s = 0; s < numRaysPerPixel; s++) {
            const double u = (double(i) + random_double()) / double(width);
            const double v = (double(height - 1 - line) + random_double()) / double(height);
            const Ray r = camera.get_ray(u, v);
            int numBounces;
            pixel += color(r, object, 0, &numBounces);
        }
        pixel /= double(numRaysPerPixel);
        pixels(i, line) = pixel;
    }
}

Vec3 Renderer::color(const Ray& r, const Object& world, int depth, int* numBounces)
{
    static int staticNumBounces;

    staticNumBounces = depth + 1;

    auto rec = world.hit(r, 0.001, std::numeric_limits<double>::max());
    Vec3 result;
    if (rec) {
        if (depth < 50) {
            auto scattered = rec->material->scatter(r, *rec);
            if (scattered) {
                result = color(*scattered, world, depth + 1);
            }
            else {
                result = Vec3(0.0, 0.0, 0.0);
            }
        }
        else {
            result = Vec3(0.0, 0.0, 0.0);
        }
    }
    else {
        Vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        result = r.color * ((1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0));
    }

    if (numBounces) {
        *numBounces = staticNumBounces;
    }
    return result;
}
