
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(LIB_BUILD "../build/src")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  GraphTests
  clientTest.cpp
  bfsTest.cpp
  dfsTest.cpp
  dijkstraTest.cpp
  graphTest.cpp
  kruskalTest.cpp
  graphFactory.h)

target_include_directories(
  GraphTests 
  PRIVATE 
  googletest/include 
  ${LIB_BUILD}
) 

target_link_libraries(
  GraphTests
  GTest::gtest_main
  GraphsLib
)

include(GoogleTest)
gtest_discover_tests(GraphTests)
