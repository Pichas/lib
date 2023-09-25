include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

set(TNAME lib_test)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
message("${sources}")
add_executable(${TNAME} ${sources})
target_include_directories(${TNAME} PUBLIC "..")

target_link_libraries(${TNAME}
 PRIVATE
  GTest::GTest
  ${PROJECT_NAME}
)

add_test(${PROJECT_NAME} ${TNAME})
