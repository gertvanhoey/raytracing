add_library(raytracing
    vector3d.h
    ray.h
    object.h
    sphere.cpp
    objectcollection.cpp
)

add_executable(raytracer 
    main.cpp
)

target_link_libraries(raytracer raytracing)

add_executable(raytracing_benchmark
    benchmark.cpp
)

target_link_libraries(raytracing_benchmark raytracing CONAN_PKG::benchmark)

if (MSVC)
  target_compile_options(raytracing PRIVATE /W4 /WX)
else()
  target_compile_options(raytracing PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Werror)
endif()
