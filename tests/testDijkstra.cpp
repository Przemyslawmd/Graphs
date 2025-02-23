
#include <chrono>
#include <memory>
#include <optional>
#include <vector>

#include <gtest/gtest.h>

#include "baseTest.h"
#include "graphFactory.h"
#include "timeType.h"

#include "algo/dijkstra.h"
#include "graph/edge.h"
#include "graph/node.h"
#include "graph/graph.h"


class DijkstraTest : public GraphTest
{
protected:

    void checkRoute(const std::map<char, route>& routes, char dstKey, std::optional<char> predecessor, int distance)
    {
        ASSERT_TRUE(routes.find(dstKey) != routes.end());
        EXPECT_EQ(routes.at(dstKey).distance, distance);
        EXPECT_EQ(routes.at(dstKey).predecessor, predecessor);
    }
};


TEST_F(DijkstraTest, FirstTest)
{
    Graph graph{ false };

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
    showDuration(begin, end);

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
    showDuration(begin, end);

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
    Graph graph{ true };
    GraphFactory::createGraph(graph, GraphType::Weighted_EightNodes);

    Dijkstra dijkstra{ graph };
    auto begin = std::chrono::high_resolution_clock::now();
    dijkstra.traverseGraph('a');
    auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

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
    Graph graph{ true };
    GraphFactory::createGraph(graph, GraphType::Weighted_TwelveNodes);

    Dijkstra dijkstra{ graph };
    auto begin = std::chrono::high_resolution_clock::now();
    dijkstra.traverseGraph('a');
    auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

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

