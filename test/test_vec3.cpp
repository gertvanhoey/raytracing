#include <catch2/catch.hpp>
#include "vector3d.h"

TEST_CASE("Vec3") {

    Vector3D v(1.0, 2.0, 3.0);
    CHECK(v[0] == 1.0);
    CHECK(v[1] == 2.0);
    CHECK(v[2] == 3.0);
}
