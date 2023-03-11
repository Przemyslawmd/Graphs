cmake_minimum_required(VERSION 3.22)
project(Graphs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(src)
if (BUILD_TESTS MATCHES ON)
    add_subdirectory(tests)
endif()
