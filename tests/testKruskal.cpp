
#include <algorithm>
#include <chrono>
#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "baseTest.h"
#include "graphFactory.h"
#include "timeType.h"

#include "algo/kruskal.h"
#include "graph/edge.h"
#include "graph/node.h"
#include "graph/graph.h"


class KruskalTest : public GraphTest
{
protected:

    bool checkEdge(std::vector<Edge>& edges, char src, char dst, size_t weight)
    {
        const Edge edgeTest{ src, dst, weight };
        return std::any_of(edges.begin(), edges.end(), [&edgeTest](auto& edge) { return edge == edgeTest; });
    }
};


TEST_F(KruskalTest, FiveNodes_Directional)
{
    Graph graph{ true } ;
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e', });

    graph.addEdgesWeighted('a', {{ 'b', 1 }, { 'c', 7 }});
    graph.addEdgesWeighted('b', {{ 'a', 1 }, { 'c', 5 }, { 'd', 4 }});
    graph.addEdgesWeighted('c', {{ 'a', 7 }, { 'e', 6 }});
    graph.addEdgesWeighted('d', {{ 'e', 2 }, { 'b', 4 }});
    graph.addEdgesWeighted('e', {{ 'b', 3 }});

    const auto begin = std::chrono::high_resolution_clock::now();
    Kruskal kruskal{ graph };
    std::unique_ptr<std::vector<Edge>> edges = kruskal.makeMinSpanningTree();
    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    EXPECT_EQ(edges->size(), 4);
    EXPECT_TRUE(checkEdge(*edges, 'a', 'b', 1));
    EXPECT_TRUE(checkEdge(*edges, 'd', 'e', 2));
    EXPECT_TRUE(checkEdge(*edges, 'e', 'b', 3));
    EXPECT_TRUE(checkEdge(*edges, 'b', 'c', 5));
}


TEST_F(KruskalTest, NineNodes_Nodirectional)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Weighted_NineNodes_Nondirectorial);

    const auto begin = std::chrono::high_resolution_clock::now();
    Kruskal kruskal{ graph };
    std::unique_ptr<std::vector<Edge>> edges = kruskal.makeMinSpanningTree();
    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    EXPECT_EQ(edges->size(), 8);
    EXPECT_TRUE(checkEdge(*edges, 'a', 'b', 4));
    EXPECT_TRUE(checkEdge(*edges, 'a', 'h', 8));
    EXPECT_TRUE(checkEdge(*edges, 'h', 'g', 1));
    EXPECT_TRUE(checkEdge(*edges, 'g', 'f', 2));
    EXPECT_TRUE(checkEdge(*edges, 'f', 'c', 4));
    EXPECT_TRUE(checkEdge(*edges, 'c', 'i', 2));
    EXPECT_TRUE(checkEdge(*edges, 'c', 'd', 7));
    EXPECT_TRUE(checkEdge(*edges, 'd', 'e', 9));
}


TEST_F(KruskalTest, TenNodes_Nodirectional)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Weighted_TenNodes_Nondirectorial);

    const auto begin = std::chrono::high_resolution_clock::now();
    Kruskal kruskal{ graph };
    std::unique_ptr<std::vector<Edge>> edges = kruskal.makeMinSpanningTree();
    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    EXPECT_EQ(edges->size(), 9);
    EXPECT_TRUE(checkEdge(*edges, 'a', 'b', 3));
    EXPECT_TRUE(checkEdge(*edges, 'a', 'f', 2));
    EXPECT_TRUE(checkEdge(*edges, 'e', 'f', 1));
    EXPECT_TRUE(checkEdge(*edges, 'e', 'g', 6));
    EXPECT_TRUE(checkEdge(*edges, 'e', 'h', 5));
    EXPECT_TRUE(checkEdge(*edges, 'e', 'i', 10));
    EXPECT_TRUE(checkEdge(*edges, 'c', 'd', 8));
    EXPECT_TRUE(checkEdge(*edges, 'd', 'i', 4));
    EXPECT_TRUE(checkEdge(*edges, 'i', 'j', 9));
}

