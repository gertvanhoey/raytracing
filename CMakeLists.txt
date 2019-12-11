cmake_minimum_required(VERSION 3.9)

# CMake
# -----

# Avoid warning about overriding '/W3' with '/W4' when compiling with MSVC
if (POLICY CMP0092)
cmake_policy(SET CMP0092 NEW)
endif()

# Project
# -------

project(raytracing LANGUAGES CXX)

# Package management
# ------------------

find_program(CONAN conan)

if (CONAN)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
       message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
       file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
                     "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_run(CONANFILE conanfile.txt
            CONAN_COMMAND ${CONAN}
            BASIC_SETUP CMAKE_TARGETS
            BUILD missing)
endif ()

# Targets
# -------

set(CMAKE_CXX_STANDARD 17)
enable_testing()

# Make sure dynamic libraries are found at runtime on Mac
set(CMAKE_MACOSX_RPATH OFF)

add_subdirectory(src)

if (NOT CONAN)
    message(WARNING "Building the benchmark and unit tests requires Conan package manager: please visit https://conan.io and install")
else()
    add_subdirectory(test)
    add_subdirectory(benchmark)
endif()
