#define _USE_MATH_DEFINES
#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "array2d.h"
#include "camera.h"
#include "material.h"
#include "objectcollection.h"
#include "renderer.h"
#include "world.h"

void saveToPPM(const std::string& filename, const Array2D<Vec3>& pixels, int width, int height)
{
    std::ofstream output;
    output.open(filename);
    output << "P3\n" << width << " " << height << "\n255\n";
    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < width; i++) {
            const Vec3 pixel = pixels(i, j);
            Vec3 encodedPixel(sqrt(pixel[0]), sqrt(pixel[1]), sqrt(pixel[2]));
            Vec3 scaledPixel(255.99 * encodedPixel.r(), 255.99 * encodedPixel.g(), 255.99 * encodedPixel.b());

            output << int(scaledPixel.r()) << " " << int(scaledPixel.g()) << " " << int(scaledPixel.b()) << "\n";
        }
    }
    output.close();
}

int main()
{
    const size_t width = 640;
    const size_t height = 480;
    const int numRaysPerPixel = 50;

    auto world = World::randomSceneHierarchy();

    const Vec3 lookFrom(12.0, 2.0, 4.0);
    const Vec3 lookAt(0.0, 0.0, 0.0);
    const double distanceToFocus = (lookFrom - lookAt).length();
    const double aperture = 0.05;
    Camera camera(
        lookFrom, lookAt, Vec3(0.0, 1.0, 0.0), 30.0, double(width) / double(height), aperture, distanceToFocus);

    auto pixelsParallel = Renderer::renderParallel(*world, camera, width, height, numRaysPerPixel, 8);
    saveToPPM("image_parallel.ppm", pixelsParallel, width, height);

    return 0;
}
