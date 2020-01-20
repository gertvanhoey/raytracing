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

# CMake modules
# -------------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(NOT WIN32)
    find_program(LCOV lcov)
    if(LCOV)
        include(CodeCoverage)
        append_coverage_compiler_flags()
        find_program(CTEST ctest)
        setup_target_for_coverage_lcov(
            NAME coverage
            EXECUTABLE ${CTEST} -j ${PROCESSOR_COUNT}
            DEPENDENCIES test_raytracing
            EXCLUDE "*/test_*.cpp"
        )
    else()
        message(WARNING "Install lcov for being able to measure code coverage")
    endif()
endif()

# Qt
# --

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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
            BASIC_SETUP CMAKE_TARGETS KEEP_RPATHS
            BUILD missing)
endif ()

# Targets
# -------

set(CMAKE_CXX_STANDARD 17)
enable_testing()

add_subdirectory(src)

if(NOT CONAN)
    message(WARNING "Building the benchmark and unit tests requires Conan package manager: please visit https://conan.io and install")
else()
    add_subdirectory(test)
    add_subdirectory(benchmark)
endif()
