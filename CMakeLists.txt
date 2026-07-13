cmake_minimum_required(VERSION 3.20)
project(mouse_front LANGUAGES CXX)
find_package(raylib REQUIRED)
add_executable(mouse_front src/main.cpp
    src/Mouse.cpp)
target_link_libraries(mouse_front PRIVATE raylib)