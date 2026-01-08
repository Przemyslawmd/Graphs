
set(GRAPH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/graph/")
set(ALGO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/algo/")

add_library(
    GraphsLib 
    STATIC 
    ${GRAPH_DIR}edge.cpp 
    ${GRAPH_DIR}graph.cpp 
    ${ALGO_DIR}bfs.cpp 
    ${ALGO_DIR}dfs.cpp 
    ${ALGO_DIR}dijkstra.cpp 
    ${ALGO_DIR}kruskal.cpp
    ${ALGO_DIR}color.cpp
    "graphclient.cpp")

target_include_directories(GraphsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

