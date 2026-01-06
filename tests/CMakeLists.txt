
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(LIB_BUILD "../build/src/")
set(TARGET_NAME "tests")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

if(UNIX)
    set(TIME_MEASUREMENT_TYPE std::chrono::system_clock::time_point)
elseif(WIN32)
    set(TIME_MEASUREMENT_TYPE std::chrono::steady_clock::time_point)
endif()
configure_file (timeType.h.in ${CMAKE_CURRENT_SOURCE_DIR}/timeType.h @ONLY)

enable_testing()

add_executable(
  ${TARGET_NAME}
  "testGraphClient.cpp"
  "testBfs.cpp"
  "testDfs.cpp"
  "testDijkstra.cpp"
  "testCreatingGraph.cpp"
  "testKruskal.cpp"
  "graphFactory.h"
  "baseTest.h"  )

target_include_directories(
  ${TARGET_NAME} 
  PRIVATE 
  googletest/include 
  ${LIB_BUILD}
) 

target_link_libraries(
  ${TARGET_NAME}
  GTest::gtest_main
  GTest::gmock
  GraphsLib
)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
