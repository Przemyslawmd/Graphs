
#include "../src/algo/kruskal.h"
#include "../src/graph/edge.h"
#include "../src/graph/node.h"
#include "../src/graph/graphList.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


void checkEdge(const Edge& edge, char src, char dst, int weight)
{
    EXPECT_EQ(edge.src, src);
    EXPECT_EQ(edge.dst, dst);
    EXPECT_EQ(edge.weight, weight);
}


TEST(TestKruskal, FirstTest)
{
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e', }; 
    GraphList graph;
    graph.addNodes(keys);

    graph.addEdgesWithWeight('a', {{ 'b', 1 }, { 'c', 7 }});
    graph.addEdgesWithWeight('b', {{ 'a', 1 }, { 'c', 5 }, { 'd', 4 }});
    graph.addEdgesWithWeight('c', {{ 'a', 7 }, { 'e', 6 }});
    graph.addEdgesWithWeight('d', {{ 'e', 2 }, { 'b', 4 }});
    graph.addEdgesWithWeight('e', {{ 'b', 3 } });

    Kruskal kruskal(graph);
    std::unique_ptr<std::vector<Edge>> edges = kruskal.makeMinSpanningTree();

    EXPECT_EQ(edges.get()->size(), 4);
    checkEdge(edges.get()->at(0), 'a', 'b', 1);
    checkEdge(edges.get()->at(1), 'd', 'e', 2);
    checkEdge(edges.get()->at(2), 'e', 'b', 3);
    checkEdge(edges.get()->at(3), 'b', 'c', 5);
}

