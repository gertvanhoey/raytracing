set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

add_library(raytracing
    vector3d.h
    ray.h
    object.h
    sphere.cpp
    objectcollection.cpp
)

target_include_directories(raytracing PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}"
)

include(GenerateExportHeader)
generate_export_header(raytracing)

if (MSVC)
  target_compile_options(raytracing PRIVATE /W4 /WX)
else()
  target_compile_options(raytracing PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Werror)
endif()


add_executable(example
    main.cpp
)
target_link_libraries(example raytracing)

if (CONAN)
    add_executable(benchmark
        benchmark.cpp
    )
    target_link_libraries(benchmark raytracing CONAN_PKG::benchmark)
endif()

