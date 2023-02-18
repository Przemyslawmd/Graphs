
#include "../src/algo/dijkstra.h"
#include "../src/graph/edge.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <memory>
#include <optional>
#include <vector>


void checkRoute(const std::map<char, route>& routes, char dstKey, std::optional<char> viaKey, int distance)
{
    ASSERT_TRUE(routes.find(dstKey) != routes.end());
    EXPECT_EQ(routes.at(dstKey).distance, distance);
    EXPECT_EQ(routes.at(dstKey).predecessor, viaKey);
}


TEST(TestDijkstra, FirstTest)
{
    Graph graph{ false, true };
    graph.addNodes({ 'a', 'b', 'c', 'd' });

    graph.addEdgesWithWeight('a', {{ 'b', 1 }, { 'd', 3 }});
    graph.addEdgesWithWeight('b', {{ 'c', 5 }, { 'd', 2 }});

    Dijkstra dijkstra(graph);
    dijkstra.traverseGraph('a');
    const auto& routes = dijkstra.getRoutes();
    
    checkRoute(routes, 'a', std::nullopt, 0);
    checkRoute(routes, 'b', 'a', 1);
    checkRoute(routes, 'c', 'b', 6);
    checkRoute(routes, 'd', 'a', 3);
}


TEST(TestDijkstra, SecondTest)
{
    Graph graph{ true, true } ;
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e', 'f' });

    graph.addEdgesWithWeight('a', {{ 'd', 5 }, { 'e', 2 }, { 'f', 8 }});
    graph.addEdgesWithWeight('b', {{ 'a', 4 }, { 'c', 5 }});
    graph.addEdgesWithWeight('d', {{ 'e', 2 }});
    graph.addEdgesWithWeight('e', {{ 'b', 4 }, { 'c', 2 }, { 'f', 1 }});
    graph.addEdgesWithWeight('f', {{ 'c', 6 }});

    Dijkstra dijkstra(graph);
    dijkstra.traverseGraph('a');
    const auto& routesA = dijkstra.getRoutes();
    
    checkRoute(routesA, 'a', std::nullopt, 0);
    checkRoute(routesA, 'b', 'e', 6);
    checkRoute(routesA, 'c', 'e', 4);
    checkRoute(routesA, 'd', 'a', 5);
    checkRoute(routesA, 'e', 'a', 2);
    checkRoute(routesA, 'f', 'e', 3);
    
    
    graph.resetNodes();
    dijkstra.traverseGraph('e');
    const auto& routesE = dijkstra.getRoutes();
    
    checkRoute(routesE, 'a',  'b', 8);
    checkRoute(routesE, 'b',  'e', 4);
    checkRoute(routesE, 'c',  'e', 2);
    checkRoute(routesE, 'd',  'a', 13);
    checkRoute(routesE, 'e',  std::nullopt, 0);
    checkRoute(routesE, 'f',  'e', 1);
}

