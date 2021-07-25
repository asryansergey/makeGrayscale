cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra")
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(greyscalePng)

option(BUILD_TESTS "Build tests" OFF)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

list(APPEND LODEPNG_INCLUDES ${PROJECT_SOURCE_DIR}/libs/lodepng)

list(APPEND GSPNG_INCLUDES ${PROJECT_SOURCE_DIR}/src/)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cc")
list(APPEND SOURCES "${LODEPNG_INCLUDES}/lodepng.cpp")

add_executable(gspng ${SOURCES})

target_include_directories(gspng PUBLIC ${LODEPNG_INCLUDES})
target_include_directories(gspng PRIVATE ${GSPNG_INCLUDES})

set_target_properties(gspng PROPERTIES ADDITIONAL_CLEAN_FILES 
    "${CMAKE_BINARY_DIR}/CMakeCache.txt")

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()