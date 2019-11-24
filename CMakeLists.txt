cmake_minimum_required(VERSION 3.0)

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
if (NOT CONAN)
    message(FATAL_ERROR "Needs conan package manager: please visit https://conan.io and install")
endif ()

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

#conan_add_remote(NAME mpusz INDEX 1 URL https://api.bintray.com/conan/mpusz/conan-mpusz)

conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

# Targets
# -------

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
