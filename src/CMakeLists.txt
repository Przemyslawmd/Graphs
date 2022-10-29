cmake_minimum_required(VERSION 3.14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(GraphsSrc)

aux_source_directory(./graph GRAPH)
aux_source_directory(./algo ALGO)
add_executable(GraphsSrc ${GRAPH} ${ALGO})

target_include_directories(GraphsSrc PUBLIC "${PROJECT_BINARY_DIR}")
