
#include "../src/algo/bfs.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"
#include "graphFactory.h"

#include <gtest/gtest.h>

#include <chrono>
#include <memory>
#include <vector>

constexpr bool measurement = true;


class BFSTest : public ::testing::Test
{
protected:

    void checkNodes(const std::vector<std::unique_ptr<Node>>& nodes, int expectedNodesCount)
    {
        ASSERT_EQ(nodes.size(), expectedNodesCount);
        for (auto& node : nodes) {
            EXPECT_TRUE(node->isVisited());
        }
    }
};


TEST_F(BFSTest, FirstTest)
{
    Graph graph{ false, false };
    GraphFactory::createGraph(graph, 1);
    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 5);
}


TEST_F(BFSTest, SecondTest)
{
    Graph graph{ false, false };
    GraphFactory::createGraph(graph, 2);
    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 7);
}


TEST_F(BFSTest, ThirdTest)
{
    Graph graph{ true, false };
    GraphFactory::createGraph(graph, 3);

    auto begin = std::chrono::high_resolution_clock::now();
    BFS bfs{ graph };
    bfs.traverseGraph();

    if (measurement) {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "BFSTest : ThirdTest : time in microseconds : " << elapsed.count() << std::endl;
    }

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 14) ;
}


TEST_F(BFSTest, FourthTest)
{
    Graph graph{ false, false };
    GraphFactory::createGraph(graph, 4);

    auto begin = std::chrono::high_resolution_clock::now();
    BFS bfs{ graph };
    bfs.traverseGraph();

    if (measurement) {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "BFSTest : FourthTest : time in microseconds : " << elapsed.count() << std::endl;
    }

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 20);
}

