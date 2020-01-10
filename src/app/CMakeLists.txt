add_executable(example
    main.cpp
)
target_link_libraries(example raytracing)


find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)

add_executable(qtrenderer
    qtmain.cpp
    qml/qml.qrc
)

target_link_libraries(qtrenderer raytracing_qt)
