cmake_minimum_required(VERSION 3.20)

project(Day12 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Part1 part1.cpp ../lib/lib.cpp)
add_executable(Part2 part2.cpp ../lib/lib.cpp)

target_include_directories(Part1 PRIVATE ../lib)
target_include_directories(Part2 PRIVATE ../lib)
