
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(GRAPH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/graph/")
set(ALGO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/algo/")

add_executable(graphs ${GRAPH_DIR}graph.cpp 
                      ${GRAPH_DIR}graphList.cpp 
                      ${GRAPH_DIR}graphMatrix.cpp 
                      ${GRAPH_DIR}node.cpp)

add_executable(algo   ${ALGO_DIR}bfs.cpp 
                      ${ALGO_DIR}dfs.cpp 
                      ${ALGO_DIR}dijkstra.cpp) 

