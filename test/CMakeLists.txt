add_executable(raytracing_test test.cpp)
target_link_libraries(raytracing_test CONAN_PKG::Catch2)
add_test(NAME raytracing_test COMMAND $<TARGET_FILE:raytracing_test>)
