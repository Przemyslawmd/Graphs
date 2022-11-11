
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(SRC "../src/")

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
  ${SRC}/algo/bfs.cpp
  ${SRC}/algo/dfs.cpp
  ${SRC}/algo/dijkstra.cpp
  ${SRC}/graph/graph.cpp
  ${SRC}/graph/graphList.cpp
  ${SRC}/graph/graphMatrix.cpp
  ${SRC}/graph/node.cpp
)

target_link_libraries(
  GraphTests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(GraphTests)
