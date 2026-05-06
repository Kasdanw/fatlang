project(fatlang_lib)

file(GLOB_RECURSE SRCS src/*.cpp)
add_library(fatlang_lib STATIC ${SRCS})
target_include_directories(fatlang_lib PUBLIC src)

file(GLOB_RECURSE TEST_SRCS test/*.cpp)

add_executable(fatlang_lib ${TEST_SRCS})
target_link_libraries(fatlang_test gtest gtest_main fatlang_lib)
