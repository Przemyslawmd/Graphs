
#include "../src/algo/dfs.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"
#include "graphFactory.h"

#include <gtest/gtest.h>

#include <chrono>
#include <ctime>
#include <memory>
#include <vector>

constexpr bool measurement = true;


class DFSTest : public ::testing::Test
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


TEST_F(DFSTest, 1)
{
    Graph graph{ false, false };
    GraphFactory::createGraph(graph, 1);

    DFS dfs{ graph };
    dfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 5);
}    


TEST_F(DFSTest, SecondTest)
{
    Graph graph{ false, false };
    GraphFactory::createGraph(graph, 2);

    DFS dfs{ graph };
    dfs.traverseGraph();
    
    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 7);
}


TEST_F(DFSTest, ThirdTest)
{
    Graph graph{ true, false };
    GraphFactory::createGraph(graph, 3);

    auto begin = std::chrono::high_resolution_clock::now();
    std::clock_t c_start = std::clock();
    DFS dfs{ graph };
    dfs.traverseGraph();

    if (measurement) {
        std::clock_t c_end = std::clock();
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "DFSTest : ThirdTest : time in microseconds : " << elapsed.count() << std::endl;
    }

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 14);
}


TEST_F(DFSTest, FourthTest)
{
    Graph graph{ false, false };
    GraphFactory::createGraph(graph, 4);

    auto begin = std::chrono::high_resolution_clock::now();
    DFS dfs{ graph };
    dfs.traverseGraph();

    if (measurement) {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::cout << "DFSTest : FourthTest : time in microseconds : " << elapsed.count() << std::endl;
    }

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 20);
}

