cmake_minimum_required(VERSION 3.13.4)
project(detection VERSION 1.0 LANGUAGES CXX)

#compilation c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

add_library(nn SHARED filtre.cpp
        pgmimg.cpp
        ppmimg.cpp
        neuronmath.cpp
        trainer.cpp
        test.cpp)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC ${MPI_LIBRARIES} nn)

if(MPI_COMPILE_FLAGS)
    set_target_properties(main PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(main PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
