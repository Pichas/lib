cmake_minimum_required(VERSION 3.5)

project(mycl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(${PROJECT_NAME} mycl.cpp)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        src)
