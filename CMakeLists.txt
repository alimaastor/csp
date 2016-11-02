cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB nqueens_SRC
    "${PROJECT_SOURCE_DIR}/*.h"
    "${PROJECT_SOURCE_DIR}/*.cpp"
)

include_directories ("${PROJECT_SOURCE_DIR}")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(nqueens ${nqueens_SRC})
