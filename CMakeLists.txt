cmake_minimum_required(VERSION 3.28)
project(astar_pathfinding)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

include_directories(.)

add_executable(astar_pathfinding
        main.cpp)