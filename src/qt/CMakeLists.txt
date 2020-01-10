add_library(raytracing_qt
    renderer_qt.cpp
    imageitem.cpp
)

target_include_directories(raytracing_qt PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(Qt5 COMPONENTS Quick REQUIRED)

target_link_libraries(raytracing_qt raytracing Qt5::Quick)

include(GenerateExportHeader)
generate_export_header(raytracing_qt)

if (MSVC)
  target_compile_options(raytracing_qt PRIVATE /W4 /WX)
else()
  target_compile_options(raytracing_qt PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion -Werror)
endif()
