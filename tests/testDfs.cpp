
#include <algorithm>
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


TEST_F(DFSTest, FirstTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FiveNodes);
    DFS dfs{ graph };

    auto sequence = dfs.traverseGraph('a');
    size_t index = 0;
    for (const char key : { 'a', 'b', 'c', 'd', 'e' }) {
        ASSERT_EQ(sequence->at(index++), key);
    }

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.isVisited(); }));
}


TEST_F(DFSTest, SecondTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_SevenNodes);
    DFS dfs{ graph };

    auto sequence = dfs.traverseGraph('a');
    size_t index = 0;
    for (const char key : { 'a', 'b', 'c', 'g', 'd', 'f', 'e' }) {
        ASSERT_EQ(sequence->at(index++), key);
    }

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.isVisited(); }));
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

    size_t index = 0;
    for (const char key : { 'a', 'd', 'b', 'c', 'i', 'f', 'e', 'h', 'g', 'j', 'k', 'l', 'n', 'm' }) {
        ASSERT_EQ(sequence->at(index++), key);
    }

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.isVisited(); }));
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

    size_t index = 0;
    for (const char key : { 'a', 'd', 'b', 'c', 'i', 'g', 'e', 'f', 'h', 'j', 'k', 'l', 'n', 'm', 't', 'r', 'p', 's', 'o', 'u' }) {
        ASSERT_EQ(sequence->at(index++), key);
    }

    const auto& nodes = graph.getNodes();
    ASSERT_TRUE(std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return node.isVisited(); }));
}

