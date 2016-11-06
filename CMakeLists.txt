cmake_minimum_required(VERSION 2.6)

file(GLOB nqueens_SRC
    "${PROJECT_SOURCE_DIR}/*.h"
    "${PROJECT_SOURCE_DIR}/*.cpp"
)
add_definitions(-Wall -Wextra -std=c++11)
include_directories ("${PROJECT_SOURCE_DIR}")
add_executable(nqueens ${nqueens_SRC})
