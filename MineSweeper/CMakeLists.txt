cmake_minimum_required(VERSION 3.24)
project(MineSweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(MineSweeper main.cpp files files/images functions.h UI.cpp UI.h Tile.cpp Tile.h Board.cpp Board.h TextureMananger.cpp TextureMananger.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(MineSweeper sfml-system sfml-window sfml-graphics sfml-audio)