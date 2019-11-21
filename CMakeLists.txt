cmake_minimum_required(VERSION 3.0)

project(raytracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracer 
    main.cpp
    vec3.h
    ray.h
    hittable.h
    sphere.h
    hittable_list.h
)

# https://foonathan.net/2018/10/cmake-warnings/

target_compile_options(raytracer PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wconversion -Wsign-conversion -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4>
)
