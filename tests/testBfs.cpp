
#include <algorithm>
#include <chrono>
#include <memory>
#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "baseTest.h"
#include "graphFactory.h"

#include "graph/node.h"
#include "graph/graph.h"
#include "algo/bfs.h"


using ::testing::ElementsAre;


class BFSTest : public GraphTest {};


TEST_F(BFSTest, FirstTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FiveNodes);
    BFS bfs{ graph };

    auto sequence = bfs.traverseGraph('a');
    EXPECT_THAT(*sequence, ElementsAre('a', 'b', 'c', 'd', 'e'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


TEST_F(BFSTest, SecondTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_SevenNodes);
    BFS bfs{ graph };

    auto sequence = bfs.traverseGraph('a');
    EXPECT_THAT(*sequence, ElementsAre('a', 'b', 'd', 'c', 'g', 'f', 'e'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


TEST_F(BFSTest, ThirdTest)
{
    Graph graph{ true };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FourteenNodes);

    BFS bfs{ graph };
    const auto begin = std::chrono::high_resolution_clock::now();
    auto sequence = bfs.traverseGraph('a');
    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    EXPECT_THAT(*sequence, ElementsAre('a', 'd', 'h', 'b', 'e', 'f', 'g', 'j', 'c', 'k', 'i', 'l', 'n', 'm'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


TEST_F(BFSTest, FourthTest)
{
    Graph graph{ true };
    GraphFactory::createGraph(graph, GraphType::Unweighted_TwentyNodes);

    BFS bfs{ graph };
    const auto begin = std::chrono::high_resolution_clock::now();
    auto sequence = bfs.traverseGraph('a');
    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    EXPECT_THAT(*sequence, ElementsAre('a', 'd', 'h', 'b', 'e', 'f', 'g', 'j', 'c', 'k', 'i', 'o', 'l', 'n', 'p', 'u', 'm', 'r', 's', 't'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


// Directed graph, node C is not a source
TEST_F(BFSTest, NodeNotSource)
{
    Graph graph{ true };
    graph.addEdge('a', 'b');
    graph.addEdge('b', 'c');
    BFS bfs{ graph };

    auto sequence = bfs.traverseGraph('a');
    EXPECT_THAT(*sequence, ElementsAre('a', 'b', 'c'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}


// Repeat traverse in the same BSF object for other source node
TEST_F(BFSTest, RepeatTraverse)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FiveNodes);
    BFS bfs{ graph };

    auto sequence = bfs.traverseGraph('a');
    EXPECT_THAT(*sequence, ElementsAre('a', 'b', 'c', 'd', 'e'));

    sequence = bfs.traverseGraph('c');
    EXPECT_THAT(*sequence, ElementsAre('c', 'b', 'd', 'e', 'a'));

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.visited; }));
}

