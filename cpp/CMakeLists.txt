cmake_minimum_required(VERSION 3.27)
project(PrisonProblem)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -funroll-loops -flto=auto -DNDEBUG -march=native -mtune=native -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(TBB REQUIRED)

file(GLOB SRCS "src/*.cpp")

add_executable(PrisonProblem ${SRCS})
target_link_libraries(PrisonProblem PRIVATE TBB::tbb)