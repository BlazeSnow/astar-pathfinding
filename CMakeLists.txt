cmake_minimum_required(VERSION 3.31)
project(astar-pathfinding LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -static")

add_executable(astar-pathfinding main.cpp)