cmake_minimum_required(VERSION 3.14)

project(tests)
set(BINARY ${CMAKE_PROJECT_NAME}Tests)

if (BUILD_TESTS)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/96f4ce02a3a78d63981c67acbd368945d11d7d70.zip
    )
    FetchContent_MakeAvailable(googletest)

    file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/../src/convertor.cc")
    list(APPEND SOURCES "${PROJECT_SOURCE_DIR}/../libs/lodepng/lodepng.cpp")

    # Create and copy test input examples into working directory fo binary
    set(TEST_INPUTS "${CMAKE_BINARY_DIR}/tests/examples")
    file(COPY "${PROJECT_SOURCE_DIR}/examples/" DESTINATION ${TEST_INPUTS})

    file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cc)

    add_executable(${BINARY} ${TEST_SOURCES} ${SOURCES})

    include(GoogleTest)
    gtest_add_tests(TARGET ${BINARY} ${TEST_SOURCES}})

    target_include_directories(${BINARY} PUBLIC "${PROJECT_SOURCE_DIR}/../libs/lodepng" )
    target_include_directories(${BINARY} PRIVATE "${PROJECT_SOURCE_DIR}/../src/")

    target_link_libraries(${BINARY} gtest gtest_main)
endif()