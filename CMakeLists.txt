cmake_minimum_required(VERSION 3.8)

project(Prueba_Rapida)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(src 
    server/src/main.cpp
    server/src/server.cpp
    server/src/game.cpp
    server/src/enemies.cpp
    server/src/genetic_algorithm.cpp
    server/src/bresenham_algorithm.cpp
    server/src/backtracking.cpp
    server/src/a-star.cpp
)

set(head
    include/server.hpp
    include/game.hpp
    include/player.hpp
    include/ghost.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/include/)


add_executable(run ${src} server/${head})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(run Threads::Threads)