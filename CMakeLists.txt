cmake_minimum_required(VERSION 3.24)
project(graphs-hw2)

add_executable(generator-connected src/generator-connected.cpp)
add_executable(generator src/generator.cpp)
add_executable(mincut src/mincut.cpp)
add_executable(radius-diameter src/radius-diameter.cpp)
add_executable(connectivity src/connectivity.cpp)
