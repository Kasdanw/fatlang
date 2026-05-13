cmake_minimum_required(VERSION 3.21)
project(fatlang)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(lib)
add_executable(fatlang src/main.cpp)
target_link_libraries(fatlang PRIVATE fatlang_lib)
target_include_directories(fatlang PRIVATE lib/src)
