cmake_minimum_required(VERSION 3.0)

# Avoid warning about overriding '/W3' with '/W4' when compiling with MSVC
if (POLICY CMP0092)
cmake_policy(SET CMP0092 NEW)
endif()

project(raytracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracer 
    main.cpp
    vector3d.h
    ray.h
    object.h
    sphere.h
    objectcollection.h
)

if (MSVC)
  target_compile_options(raytracer PRIVATE /W4 /WX)
else()
  target_compile_options(raytracer PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Werror)
endif()
