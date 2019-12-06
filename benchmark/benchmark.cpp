#include <benchmark/benchmark.h>
#include "objectcollection.h"
#include "sphere.h"
#include "lambertian.h"

Vec3 color(const Ray& r, const Object& world) {
    Vec3 result;
    auto rec = world.hit(r, 0.0, std::numeric_limits<double>::max());
    if (rec) {
        auto normal = rec->normal;
        result = 0.5 * Vec3(normal.x() + 1.0, normal.y() + 1.0, normal.z() + 1.0);
    }
    else {
        Vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        result = (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
    }
    return result;
}

static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
      const int width = 1920;
      const int height = 1080;

      Vec3 lower_left_corner(-2.0, -1.0, -1.0);
      Vec3 horizontal(4.0, 0.0, 0.0);
      Vec3 vertical(0.0, 2.0, 0.0);
      Vec3 origin(0.0, 0.0, 0.0);

      std::vector<std::unique_ptr<Object>> list;

      auto world = std::make_unique<ObjectCollection>();
      world->add(std::make_unique<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5, std::make_shared<Lambertian>(Vec3(0.8, 0.3, 0.3))));
      world->add(std::make_unique<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0, std::make_shared<Lambertian>(Vec3(0.8, 0.8, 0.0))));

      std::vector<Vec3> pixels(width * height);
      for (int j = height - 1; j >= 0; j--) {
          for (int i = 0; i < width; i++) {
              double u = double(i) / double(width);
              double v = double(j) / double(height);
              Ray r(origin,
                    lower_left_corner + u * horizontal + v * vertical,
                    Vec3(1.0, 1.0, 1.0));

              Vec3 col = color(r, *world);

              pixels[i + (height - j - 1) * width] = Vec3(255.99 * col.r(), 255.99 * col.g(), 255.99 * col.b());
          }
      }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);
// Run the benchmark
BENCHMARK_MAIN();