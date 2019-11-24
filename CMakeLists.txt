cmake_minimum_required(VERSION 3.0)

# Avoid warning about overriding '/W3' with '/W4' when compiling with MSVC
if (POLICY CMP0092)
cmake_policy(SET CMP0092 NEW)
endif()

project(raytracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
