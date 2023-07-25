cmake_minimum_required(VERSION 3.25)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(Minesweeper main.cpp src/board.cpp)

target_include_directories(Minesweeper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})