cmake_minimum_required(VERSION 3.20)
project(mouse_front LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(mouse_front src/main.cpp
    src/Mouse.cpp
    src/Game.cpp
    src/Maze.cpp
    src/screens/MainMenuScreen.cpp
    src/screens/ProfileSetupScreen.cpp
    src/screens/IntroScreen.cpp
    src/GameApp.cpp)
    
target_link_libraries(mouse_front PRIVATE raylib)