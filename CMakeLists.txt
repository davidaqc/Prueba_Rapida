cmake_minimum_required(VERSION 3.8)

project(server)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(src 
    server/src/main.cpp
    #server/src/genetic_algorithm.cpp
    server/src/bresenham_algorithm.cpp
    #server/src/backtracking.cpp
    #server/src/a-star.cpp
)

set(head
    server/include/algorithms.hpp
    server/include/aixlog.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/server/include/)


add_executable(run ${src} ${head})
