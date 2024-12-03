cmake_minimum_required(VERSION 3.20)

project(Day3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(part1 part1.cpp ../lib/lib.cpp)
add_executable(part2 part2.cpp ../lib/lib.cpp)

target_include_directories(part1 PRIVATE ../lib)
target_include_directories(part2 PRIVATE ../lib)
