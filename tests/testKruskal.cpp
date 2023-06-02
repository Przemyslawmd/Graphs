
#include "graphFactory.h"
#include "../src/algo/kruskal.h"
#include "../src/graph/edge.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <memory>
#include <vector>

constexpr bool measurement = false;


bool checkEdge(std::vector<Edge>* edges, char src, char dst, int weight)
{
    const Edge edgeToCheck{ src, dst, weight };
    return std::any_of(edges->begin(), edges->end(), [&edgeToCheck](auto& edge) { return edge == edgeToCheck; });
}


TEST(TestKruskal, FirstTest)
{
    Graph graph{ true, true } ;
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e', });

    graph.addEdgesWeighted('a', {{ 'b', 1 }, { 'c', 7 }});
    graph.addEdgesWeighted('b', {{ 'a', 1 }, { 'c', 5 }, { 'd', 4 }});
    graph.addEdgesWeighted('c', {{ 'a', 7 }, { 'e', 6 }});
    graph.addEdgesWeighted('d', {{ 'e', 2 }, { 'b', 4 }});
    graph.addEdgesWeighted('e', {{ 'b', 3 } });

    auto begin = std::chrono::high_resolution_clock::now();
    Kruskal kruskal{ graph };
    std::unique_ptr<std::vector<Edge>> edges = kruskal.makeMinSpanningTree();
    if (measurement) {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "TestKruskal : FirstTest : time in microseconds : " << elapsed.count() << std::endl;
    }

    EXPECT_EQ(edges.get()->size(), 4);
    EXPECT_TRUE(checkEdge(edges.get(), 'a', 'b', 1));
    EXPECT_TRUE(checkEdge(edges.get(), 'd', 'e', 2));
    EXPECT_TRUE(checkEdge(edges.get(), 'e', 'b', 3));
    EXPECT_TRUE(checkEdge(edges.get(), 'b', 'c', 5));
}


TEST(TestKruskal, SecondTest)
{
    Graph graph{ false, true };
    GraphFactory::createGraph(graph, GraphType::Weighted_NineNodes_Nondirectorial);

    auto begin = std::chrono::high_resolution_clock::now();
    Kruskal kruskal{ graph };
    std::unique_ptr<std::vector<Edge>> edges = kruskal.makeMinSpanningTree();
    if (measurement) {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "TestKruskal : SecondTest : time in microseconds : " << elapsed.count() << std::endl;
    }

    EXPECT_EQ(edges.get()->size(), 8);
    EXPECT_TRUE(checkEdge(edges.get(), 'a', 'b', 4));
    EXPECT_TRUE(checkEdge(edges.get(), 'a', 'h', 8));
    EXPECT_TRUE(checkEdge(edges.get(), 'h', 'g', 1));
    EXPECT_TRUE(checkEdge(edges.get(), 'g', 'f', 2));
    EXPECT_TRUE(checkEdge(edges.get(), 'f', 'c', 4));
    EXPECT_TRUE(checkEdge(edges.get(), 'c', 'i', 2));
    EXPECT_TRUE(checkEdge(edges.get(), 'c', 'd', 7));
    EXPECT_TRUE(checkEdge(edges.get(), 'd', 'e', 9));
}

