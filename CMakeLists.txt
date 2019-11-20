cmake_minimum_required(VERSION 3.0)

project(raytracing LANGUAGES CXX)

add_executable(raytracer 
    main.cpp
    vec3.h
    ray.h
    hittable.h
    sphere.h
    hittable_list.h
)
