
cmake_minimum_required(VERSION 3.22)
project(GraphsLib)

set(GRAPH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/graph/")
set(ALGO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/algo/")

add_library(
    GraphsLib 
    STATIC 
    ${GRAPH_DIR}graph.cpp 
    ${GRAPH_DIR}node.cpp
    ${ALGO_DIR}bfs.cpp 
    ${ALGO_DIR}dfs.cpp 
    ${ALGO_DIR}dijkstra.cpp 
    ${ALGO_DIR}kruskal.cpp
    graphclient.cpp
)

