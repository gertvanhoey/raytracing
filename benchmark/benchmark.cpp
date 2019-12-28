#include <benchmark/benchmark.h>
#include "world.h"
#include "camera.h"
#include "renderer.h"

static void BM_RenderRandomScene(benchmark::State& state) {

    int numThreads = state.range(0);

    const size_t width = 160;
    const size_t height = 120;
    const int numRaysPerPixel = 100;

    auto world = World::randomScene();

    const Vec3 lookFrom(12.0, 2.0, 4.0);
    const Vec3 lookAt(0.0, 0.0, 0.0);
    const double distanceToFocus = (lookFrom - lookAt).length();
    const double aperture = 0.05;
    Camera camera(lookFrom, lookAt, Vec3(0.0, 1.0, 0.0), 30.0, double(width) / double(height), aperture, distanceToFocus);

    for (auto _ : state) {

        if (numThreads == 1) {
            auto pixels = Renderer::render(*world, camera, width, height, numRaysPerPixel);
        }
        else {
            auto pixels = Renderer::renderParallel(*world, camera, width, height, numRaysPerPixel, numThreads);
        }
    }
}

BENCHMARK(BM_RenderRandomScene)->RangeMultiplier(2)->Range(1, 16)->MeasureProcessCPUTime()->UseRealTime();

BENCHMARK_MAIN();
