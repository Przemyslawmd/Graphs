
#include <algorithm>
#include <chrono>
#include <ctime>
#include <memory>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "baseTest.h"
#include "graphFactory.h"

#include "algo/dfs.h"
#include "graph/node.h"
#include "graph/graph.h"


using ::testing::ElementsAre;


class DFSTest : public GraphTest {};


TEST_F(DFSTest, FirstTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FiveNodes);
    DFS dfs{ graph };

    auto sequence = dfs.traverseGraph('a');
    EXPECT_THAT(*sequence, ElementsAre('a', 'b', 'c', 'd', 'e'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


TEST_F(DFSTest, SecondTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_SevenNodes);
    DFS dfs{ graph };

    auto sequence = dfs.traverseGraph('a');
    EXPECT_THAT(*sequence, ElementsAre('a', 'b', 'c', 'g', 'd', 'f', 'e'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


TEST_F(DFSTest, ThirdTest)
{
    Graph graph{ true };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FourteenNodes);

    const auto begin = std::chrono::high_resolution_clock::now();
    std::clock_t c_start = std::clock();
    DFS dfs{ graph };
    auto sequence = dfs.traverseGraph('a');
    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    EXPECT_THAT(*sequence, ElementsAre('a', 'd', 'b', 'c', 'i', 'f', 'e', 'h', 'g', 'j', 'k', 'l', 'n', 'm'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


TEST_F(DFSTest, FourthTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_TwentyNodes);

    auto begin = std::chrono::high_resolution_clock::now();
    DFS dfs{ graph };
    auto sequence = dfs.traverseGraph('a');
    auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    EXPECT_THAT(*sequence, ElementsAre(
        'a', 'd', 'b', 'c', 'i', 'g', 'e', 'f', 'h', 'j', 'k', 'l', 'n', 'm', 't', 'r', 'p', 's', 'o', 'u'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


// Directed graph, node D is not a source
TEST_F(DFSTest, NodeNotSource)
{
    Graph graph{ true };
    graph.addEdge('a', 'b');
    graph.addEdge('b', 'c');
    graph.addEdge('c', 'd');
    DFS bfs{ graph };

    auto sequence = bfs.traverseGraph('a');
    EXPECT_THAT(*sequence, ElementsAre('a', 'b', 'c', 'd'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


// Repeat traverse in the same DFS object for other source node
TEST_F(DFSTest, RepeatTraverse)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_SevenNodes);
    DFS dfs{ graph };

    auto sequence = dfs.traverseGraph('a');
    EXPECT_THAT(*sequence, ElementsAre('a', 'b', 'c', 'g', 'd', 'f', 'e'));

    sequence = dfs.traverseGraph('g');
    EXPECT_THAT(*sequence, ElementsAre('g', 'b', 'a', 'd', 'f', 'e', 'c'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}

