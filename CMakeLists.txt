cmake_minimum_required(VERSION 3.5)

project(myProj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

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
            entt
            mycl
            rnd
)

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            inc
            lib
            rnd
)
