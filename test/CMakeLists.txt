cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories ("${PROJECT_SOURCE_DIR}/..")

file(GLOB tests_SRC
    "${PROJECT_SOURCE_DIR}/*.h"
    "${PROJECT_SOURCE_DIR}/*.cpp"
)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${tests_SRC})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

