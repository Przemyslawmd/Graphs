
#include "graphFactory.h"
#include "timeType.h"
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


void showTime(TIME_TYPE start, TIME_TYPE end)
{
    const char* testCase = ::testing::UnitTest::GetInstance()->current_test_info()->test_case_name();
    const char* testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::setw(12) << testCase << std::setw(12) << testName <<" : time in microseconds : " << elapsed.count() << std::endl;
}


TEST(TestKruskal, FiveNodes_Directional)
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
    auto end = std::chrono::high_resolution_clock::now();
    if (measurement) {
        showTime(begin, end);
    }

    EXPECT_EQ(edges.get()->size(), 4);
    EXPECT_TRUE(checkEdge(edges.get(), 'a', 'b', 1));
    EXPECT_TRUE(checkEdge(edges.get(), 'd', 'e', 2));
    EXPECT_TRUE(checkEdge(edges.get(), 'e', 'b', 3));
    EXPECT_TRUE(checkEdge(edges.get(), 'b', 'c', 5));
}


TEST(TestKruskal, NineNodes_Nodirectional)
{
    Graph graph{ false, true };
    GraphFactory::createGraph(graph, GraphType::Weighted_NineNodes_Nondirectorial);

    auto begin = std::chrono::high_resolution_clock::now();
    Kruskal kruskal{ graph };
    std::unique_ptr<std::vector<Edge>> edges = kruskal.makeMinSpanningTree();
    auto end = std::chrono::high_resolution_clock::now();
    if (measurement) {
        showTime(begin, end);
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


TEST(TestKruskal, TenNodes_Nodirectional)
{
    Graph graph{ false, true };
    GraphFactory::createGraph(graph, GraphType::Weighted_TenNodes_Nondirectorial);

    auto begin = std::chrono::high_resolution_clock::now();
    Kruskal kruskal{ graph };
    std::unique_ptr<std::vector<Edge>> edges = kruskal.makeMinSpanningTree();
    auto end = std::chrono::high_resolution_clock::now();
    if (measurement) {
        showTime(begin, end);
    }

    EXPECT_EQ(edges.get()->size(), 9);
    EXPECT_TRUE(checkEdge(edges.get(), 'a', 'b', 3));
    EXPECT_TRUE(checkEdge(edges.get(), 'a', 'f', 2));
    EXPECT_TRUE(checkEdge(edges.get(), 'e', 'f', 1));
    EXPECT_TRUE(checkEdge(edges.get(), 'e', 'g', 6));
    EXPECT_TRUE(checkEdge(edges.get(), 'e', 'h', 5));
    EXPECT_TRUE(checkEdge(edges.get(), 'e', 'i', 10));
    EXPECT_TRUE(checkEdge(edges.get(), 'c', 'd', 8));
    EXPECT_TRUE(checkEdge(edges.get(), 'd', 'i', 4));
    EXPECT_TRUE(checkEdge(edges.get(), 'i', 'j', 9));
}

