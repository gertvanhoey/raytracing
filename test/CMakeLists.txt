set(TEST_NAMES
    Vec3
)

foreach(name ${TEST_NAMES})
    string(TOLOWER ${name} lower_name)
    list(APPEND TEST_SOURCES "test_${lower_name}.cpp")
endforeach()

add_executable(test_raytracing test.cpp ${TEST_SOURCES})
target_link_libraries(test_raytracing PRIVATE raytracing CONAN_PKG::Catch2)

foreach(name ${TEST_NAMES})
    add_test(NAME ${name} COMMAND $<TARGET_FILE:test_raytracing> ${name})
endforeach()