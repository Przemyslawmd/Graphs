
#include <chrono>
#include <ctime>
#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "baseTest.h"
#include "graphFactory.h"
#include "../src/algo/dfs.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"


class DFSTest : public GraphTest {};


TEST_F(DFSTest, 1)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FiveNodes);

    DFS dfs{ graph };
    dfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 5);
}


TEST_F(DFSTest, SecondTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_SevenNodes);

    DFS dfs{ graph };
    dfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 7);
}


TEST_F(DFSTest, ThirdTest)
{
    Graph graph{ true };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FourteenNodes);

    const auto begin = std::chrono::high_resolution_clock::now();
    std::clock_t c_start = std::clock();
    DFS dfs{ graph };
    dfs.traverseGraph();

    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 14);
}


TEST_F(DFSTest, FourthTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_TwentyNodes);

    auto begin = std::chrono::high_resolution_clock::now();
    DFS dfs{ graph };
    dfs.traverseGraph();

    auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 20);
}

