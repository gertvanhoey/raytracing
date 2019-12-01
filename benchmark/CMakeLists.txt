add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark raytracing CONAN_PKG::benchmark)
