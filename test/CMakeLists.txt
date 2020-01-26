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
    if(WIN32)
        # Add raytracing.dll to path when unit test is run via ctest
        # Approach taken from "Professional CMake", 5th edition, 28.6, p. 430
        set_tests_properties(${name} PROPERTIES ENVIRONMENT "PATH=$<SHELL_PATH:$<TARGET_FILE_DIR:raytracing>>$<SEMICOLON>$ENV{PATH}")
    endif()
endforeach()
