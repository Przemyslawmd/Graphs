
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(SRC_GRAPH "../src/graph")
set(SRC_ALGO "../src/algo")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(googletest/include) 

add_executable(
  GraphTests
  bfsTest.cpp
  dfsTest.cpp
  dijkstraTest.cpp
  graphTest.cpp
  ${SRC_ALGO}/bfs.cpp
  ${SRC_ALGO}/dfs.cpp
  ${SRC_ALGO}/dijkstra.cpp
  ${SRC_GRAPH}/graph.cpp
  ${SRC_GRAPH}/graphList.cpp
  ${SRC_GRAPH}/graphMatrix.cpp
  ${SRC_GRAPH}/node.cpp
)

target_link_libraries(
  GraphTests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(GraphTests)
