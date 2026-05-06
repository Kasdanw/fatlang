cmake_minimum_required(VERSION 3.21)
project(fatlang)

set(CMAKE_CXX_STANDART 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(fatlang main.cpp)
