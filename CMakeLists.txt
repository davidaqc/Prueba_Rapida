cmake_minimum_required(VERSION 3.8)

project(Prueba_Rapida)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(src 
    server/src/main.cpp
)

set(head
    #include/game.hpp
)

include_directories(${PROJECT_SOURCE_DIR}/include/)


add_executable(run ${src} ${head})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(run Threads::Threads)