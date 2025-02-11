
#include <chrono>
#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "baseTest.h"
#include "graphFactory.h"

#include "graph/node.h"
#include "graph/graph.h"
#include "algo/bfs.h"


class BFSTest : public GraphTest {};


TEST_F(BFSTest, FirstTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FiveNodes);
    BFS bfs{ graph };

    auto sequence = bfs.traverseGraph('a');
    size_t index = 0;
    for (const char key : { 'a', 'b', 'c', 'd', 'e' }) {
        ASSERT_EQ(sequence->at(index++), key);
    }

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.isVisited(); }));
}


TEST_F(BFSTest, SecondTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_SevenNodes);
    BFS bfs{ graph };

    auto sequence = bfs.traverseGraph('a');
    size_t index = 0;
    for (const char key : { 'a', 'b', 'd', 'c', 'g', 'f', 'e' }) {
        ASSERT_EQ(sequence->at(index++), key);
    }

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.isVisited(); }));
}


TEST_F(BFSTest, ThirdTest)
{
    Graph graph{ true };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FourteenNodes);

    const auto begin = std::chrono::high_resolution_clock::now();
    BFS bfs{ graph };
    auto sequence = bfs.traverseGraph('a');
    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    size_t index = 0;
    for (const char key : { 'a', 'd', 'h', 'b', 'e', 'f', 'g', 'j', 'c', 'k', 'i', 'l', 'n', 'm' }) {
        ASSERT_EQ(sequence->at(index++), key);
    }

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.isVisited(); }));
}


TEST_F(BFSTest, FourthTest)
{
    Graph graph{ true };
    GraphFactory::createGraph(graph, GraphType::Unweighted_TwentyNodes);

    const auto begin = std::chrono::high_resolution_clock::now();
    BFS bfs{ graph };
    auto sequence = bfs.traverseGraph('a');
    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    size_t index = 0;
    for (const char key : { 'a', 'd', 'h','b', 'e', 'f', 'g', 'j', 'c', 'k', 'i', 'o', 'l', 'n', 'p', 'u', 'm', 'r', 's', 't' }) {
        ASSERT_EQ(sequence->at(index++), key);
    }

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.isVisited(); }));
}


TEST_F(BFSTest, NodeNotSource)
{
    Graph graph{ true };
    graph.addEdge('a', 'b');
    graph.addEdge('b', 'c');
    BFS bfs{ graph };

    auto sequence = bfs.traverseGraph('a');
    size_t index = 0;
    for (const char key : { 'a', 'b', 'c' }) {
        ASSERT_EQ(sequence->at(index++), key);
    }

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.isVisited(); }));
}

