#define _USE_MATH_DEFINES
#include <cmath>
#include <cfloat>
#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <fstream>
#include "objectcollection.h"
#include "camera.h"
#include "material.h"
#include "renderer.h"
#include "world.h"

void save_to_ppm(const std::string& filename, const std::vector<Vec3>& pixels, int width, int height) {
    std::ofstream output;
    output.open(filename);
    output << "P3\n" << width << " " << height << "\n255\n";
    for (const auto& pixel : pixels) {
        Vec3 encodedPixel(sqrt(pixel[0]), sqrt(pixel[1]), sqrt(pixel[2]));
        Vec3 scaledPixel(255.99 * encodedPixel.r(), 255.99 * encodedPixel.g(), 255.99 * encodedPixel.b());

        output << int(scaledPixel.r()) << " " << int(scaledPixel.g()) << " " << int(scaledPixel.b()) << "\n";
    }
    output.close();
}

int main() {
    const int width = 160;
    const int height = 120;
    const int numRaysPerPixel = 100;

    auto world = World::randomScene();

    const Vec3 lookFrom(12.0, 2.0, 4.0);
    const Vec3 lookAt(0.0, 0.0, 0.0);
    const double distanceToFocus = (lookFrom - lookAt).length();
    const double aperture = 0.05;
    Camera camera(lookFrom, lookAt, Vec3(0.0, 1.0, 0.0), 30.0, double(width) / double(height), aperture, distanceToFocus);

    auto pixels = Renderer::render(*world, camera, width, height, numRaysPerPixel);

    save_to_ppm("image.ppm", pixels, width, height);

    return 0;
}
