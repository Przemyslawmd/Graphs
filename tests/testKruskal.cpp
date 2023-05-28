
#include "../src/algo/kruskal.h"
#include "../src/graph/edge.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <chrono>
#include <memory>
#include <vector>

constexpr bool measurement = false;


void checkEdge(const Edge& edge, char src, char dst, int weight)
{
    EXPECT_EQ(edge.src, src);
    EXPECT_EQ(edge.dst, dst);
    EXPECT_EQ(edge.weight, weight);
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
        std::clock_t c_end = std::clock();
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "TestKruskal : FirstTest : time in microseconds : " << elapsed.count() << std::endl;
    }

    EXPECT_EQ(edges.get()->size(), 4);
    checkEdge(edges.get()->at(0), 'a', 'b', 1);
    checkEdge(edges.get()->at(1), 'd', 'e', 2);
    checkEdge(edges.get()->at(2), 'e', 'b', 3);
    checkEdge(edges.get()->at(3), 'b', 'c', 5);
}

