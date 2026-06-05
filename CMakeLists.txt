cmake_minimum_required(VERSION 3.16)
project(Gambit)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

add_executable(Gambit
    src/main.cpp
    src/core/Board.cpp
    src/rendering/Renderer.cpp
    src/input/InputHandler.cpp
    src/pieces/pawn.cpp
    src/pieces/knight.cpp
    src/pieces/rook.cpp
    src/pieces/bishop.cpp
    src/pieces/queen.cpp
    src/pieces/king.cpp
)

target_include_directories(Gambit PRIVATE include)

target_link_libraries(Gambit PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)