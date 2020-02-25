cmake_minimum_required(VERSION 3.13.4)
project(detection VERSION 1.0 LANGUAGES CXX)

#compilation c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(filtre SHARED filtre.cpp
        pgmimg.cpp
        ppmimg.cpp
        neuronmath.cpp
        trainer.cpp
        test.cpp)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC filtre)
