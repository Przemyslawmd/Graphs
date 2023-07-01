
#include "../src/algo/dijkstra.h"
#include "../src/graph/edge.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"
#include "graphFactory.h"
#include "timeType.h"

#include <gtest/gtest.h>

#include <chrono>
#include <memory>
#include <optional>
#include <vector>

constexpr bool measurement = true;


class DijkstraTest : public ::testing::Test
{
protected:

    void checkRoute(const std::map<char, route>& routes, char dstKey, std::optional<char> predecessor, int distance)
    {
        ASSERT_TRUE(routes.find(dstKey) != routes.end());
        EXPECT_EQ(routes.at(dstKey).distance, distance);
        EXPECT_EQ(routes.at(dstKey).predecessor, predecessor);
    }

    void showTime(TIME_TYPE start, TIME_TYPE end)
    {
        const char* testCase = ::testing::UnitTest::GetInstance()->current_test_info()->test_case_name();
        const char* testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(12) << testCase << std::setw(12) << testName << " : time in microseconds : " << elapsed.count() << std::endl;
    }
};


TEST_F(DijkstraTest, FirstTest)
{
    Graph graph{ false, true };

    graph.addEdgesWeighted('a', {{ 'b', 1 }, { 'd', 3 }});
    graph.addEdgesWeighted('b', {{ 'c', 5 }, { 'd', 2 }});

    Dijkstra dijkstra{ graph };
    dijkstra.traverseGraph('a');
    
    const auto& routes = dijkstra.getRoutes();
    checkRoute(routes, 'a', std::nullopt, 0);
    checkRoute(routes, 'b', 'a', 1);
    checkRoute(routes, 'c', 'b', 6);
    checkRoute(routes, 'd', 'a', 3);
}


TEST_F(DijkstraTest, SecondTest)
{
    Graph graph;

    graph.addEdgesWeighted('a', {{ 'd', 5 }, { 'e', 2 }, { 'f', 8 }});
    graph.addEdgesWeighted('b', {{ 'a', 4 }, { 'c', 5 }});
    graph.addEdgesWeighted('d', {{ 'e', 2 }});
    graph.addEdgesWeighted('e', {{ 'b', 4 }, { 'c', 2 }, { 'f', 1 }});
    graph.addEdgesWeighted('f', {{ 'c', 6 }});

    Dijkstra dijkstra{ graph };

    auto begin = std::chrono::high_resolution_clock::now();
    dijkstra.traverseGraph('a');
    auto end = std::chrono::high_resolution_clock::now();
    if (measurement) {
        showTime(begin, end);
    }

    const auto& routesA = dijkstra.getRoutes();
    checkRoute(routesA, 'a', std::nullopt, 0);
    checkRoute(routesA, 'b', 'e', 6);
    checkRoute(routesA, 'c', 'e', 4);
    checkRoute(routesA, 'd', 'a', 5);
    checkRoute(routesA, 'e', 'a', 2);
    checkRoute(routesA, 'f', 'e', 3);
    
    begin = std::chrono::high_resolution_clock::now();
    dijkstra.traverseGraph('e');
    end = std::chrono::high_resolution_clock::now();
    if (measurement) {
        showTime(begin, end);
    }

    const auto& routesE = dijkstra.getRoutes();
    checkRoute(routesE, 'a',  'b', 8);
    checkRoute(routesE, 'b',  'e', 4);
    checkRoute(routesE, 'c',  'e', 2);
    checkRoute(routesE, 'd',  'a', 13);
    checkRoute(routesE, 'e',  std::nullopt, 0);
    checkRoute(routesE, 'f',  'e', 1);
}


TEST_F(DijkstraTest, ThirdTest)
{
    Graph graph{ true, true };
    GraphFactory::createGraph(graph, GraphType::Weighted_EightNodes);

    Dijkstra dijkstra{ graph };
    auto begin = std::chrono::high_resolution_clock::now();
    dijkstra.traverseGraph('a');
    auto end = std::chrono::high_resolution_clock::now();
    if (measurement) {
        showTime(begin, end);
    }

    const auto& routes = dijkstra.getRoutes();
    checkRoute(routes, 'a', std::nullopt, 0);
    checkRoute(routes, 'b', 'd', 5);
    checkRoute(routes, 'c', 'e', 9);
    checkRoute(routes, 'd', 'a', 3);
    checkRoute(routes, 'e', 'd', 4);
    checkRoute(routes, 'f', 'd', 11);
    checkRoute(routes, 'g', 'h', 11);
    checkRoute(routes, 'h', 'a', 5);
}


TEST_F(DijkstraTest, FourthTest)
{
    Graph graph{ true, true };
    GraphFactory::createGraph(graph, GraphType::Weighted_TwelveNodes);

    Dijkstra dijkstra{ graph };
    auto begin = std::chrono::high_resolution_clock::now();
    dijkstra.traverseGraph('a');
    auto end = std::chrono::high_resolution_clock::now();
    if (measurement) {
        showTime(begin, end);
    }

    const auto& routes = dijkstra.getRoutes();
    checkRoute(routes, 'a', std::nullopt, 0);
    checkRoute(routes, 'b', 'd', 5);
    checkRoute(routes, 'c', 'e', 9);
    checkRoute(routes, 'd', 'a', 3);
    checkRoute(routes, 'e', 'd', 4);
    checkRoute(routes, 'f', 'd', 11);
    checkRoute(routes, 'g', 'h', 11);
    checkRoute(routes, 'h', 'a', 5);
    checkRoute(routes, 'i', 'b', 6);
    checkRoute(routes, 'j', 'e', 11);
    checkRoute(routes, 'k', 'i', 12);
    checkRoute(routes, 'l', 'h', 9);
}

