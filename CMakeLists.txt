cmake_minimum_required(VERSION 3.5)

project(myProj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
enable_testing()

add_definitions(-DSIL_MEM_TEST)

add_subdirectory(lib)
add_subdirectory(inc)
add_subdirectory(rnd)

add_executable(
    ${PROJECT_NAME}
        main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            library
            predefined_class
            rnd
)

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            inc
            lib
            rnd
)
