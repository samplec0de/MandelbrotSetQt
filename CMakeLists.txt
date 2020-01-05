cmake_minimum_required(VERSION 3.5)
project(Mandelbrot)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Mandelbrot
        main.cpp
        Complex.cpp
        mainwindow.cpp
        )

target_link_libraries(Mandelbrot Qt5::Widgets)



