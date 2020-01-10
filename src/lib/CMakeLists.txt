add_library(raytracing
    aabb.cpp
    bvhnode.cpp
    camera.cpp
    dielectric.cpp
    lambertian.cpp
    material.cpp
    metal.cpp
    objectcollection.cpp
    renderer.cpp
    sphere.cpp
    world.cpp
)

target_include_directories(raytracing PUBLIC
    "${CMAKE_SOURCE_DIR}/include/raytracing"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

find_package(Threads)

target_link_libraries(raytracing ${CMAKE_THREAD_LIBS_INIT})

include(GenerateExportHeader)
generate_export_header(raytracing)

if (MSVC)
  target_compile_options(raytracing PRIVATE /W4 /WX)
else()
  target_compile_options(raytracing PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Werror)
endif()
