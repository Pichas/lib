project(library)

add_library(${PROJECT_NAME} memory_tree.cpp node_pool.cpp)
add_subdirectory(tests)
