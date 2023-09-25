cmake_minimum_required(VERSION 3.5)

project(entt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(${PROJECT_NAME} settings.cpp avl.cpp)

add_subdirectory(tests)
