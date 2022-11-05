
#include "../src/algo/dijkstra.h"
#include "../src/graph/edge.h"
#include "../src/graph/node.h"
#include "../src/graph/graphList.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


void checkRoute(const std::map<char, route>& routes, char dstKey, char viaKey, int distance)
{
    ASSERT_TRUE(routes.find(dstKey) != routes.end());
    EXPECT_EQ(routes.at(dstKey).distance, distance);
    EXPECT_EQ(routes.at(dstKey).predecessor, viaKey);
}


TEST(TestDijkstra, FirstTest)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D' }; 
    GraphList graph;
    graph.addNodes(keys);

    graph.addEdgesWithWeight('A', {{ 'B', 1 }, { 'D', 3 }});
    graph.addEdgesWithWeight('B', {{ 'C', 5 }, { 'D', 2 }});

    Dijkstra dikstra(graph);
    dikstra.traverseGraph('A');
    const auto& routes = dikstra.getRoutes();
    
    checkRoute(routes, 'A', '\0', 0);
    checkRoute(routes, 'B',  'A', 1);
    checkRoute(routes, 'C',  'B', 6);
    checkRoute(routes, 'D',  'A', 3);
}


TEST(TestDijkstra, SecondTest)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D', 'E', 'F' }; 
    GraphList graph;
    graph.addNodes(keys);

    graph.addEdgesWithWeight('A', {{ 'D', 5 }, { 'E', 2 }, { 'F', 8 }});
    graph.addEdgesWithWeight('B', {{ 'A', 4 }, { 'C', 5 }});
    graph.addEdgesWithWeight('D', {{ 'E', 2 }});
    graph.addEdgesWithWeight('E', {{ 'B', 4 }, { 'C', 2 }, { 'F', 1 }});
    graph.addEdgesWithWeight('F', {{ 'C', 6 }});

    Dijkstra dijkstra(graph);
    dijkstra.traverseGraph('A');
    const auto& routesA = dijkstra.getRoutes();
    
    checkRoute(routesA, 'A', '\0', 0);
    checkRoute(routesA, 'B',  'E', 6);
    checkRoute(routesA, 'C',  'E', 4);
    checkRoute(routesA, 'D',  'A', 5);
    checkRoute(routesA, 'E',  'A', 2);
    checkRoute(routesA, 'F',  'E', 3);
    
    
    graph.resetNodes();
    dijkstra.traverseGraph('E');
    const auto& routesE = dijkstra.getRoutes();
    
    checkRoute(routesE, 'A',  'B', 8);
    checkRoute(routesE, 'B',  'E', 4);
    checkRoute(routesE, 'C',  'E', 2);
    checkRoute(routesE, 'D',  'A', 13);
    checkRoute(routesE, 'E', '\0', 0);
    checkRoute(routesE, 'F',  'E', 1);
}

