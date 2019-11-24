add_executable(raytracer 
    main.cpp
    vector3d.h
    ray.h
    object.h
    sphere.cpp
    objectcollection.cpp
)

if (MSVC)
  target_compile_options(raytracer PRIVATE /W4 /WX)
else()
  target_compile_options(raytracer PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Werror)
endif()
