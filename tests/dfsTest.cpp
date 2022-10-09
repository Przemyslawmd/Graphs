

#include "../src/dfs/dfs.h"
#include "../src/graph/Node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


TEST(runTestDFS, 1)
{
    std::vector<std::vector<char>> adjacency = { { 'A', 'B' },
                                                 { 'B', 'A', 'C' },
                                                 { 'C', 'B', 'D', 'E'},
                                                 { 'D', 'C', 'E' },
                                                 { 'E', 'C', 'D'} };

    Graph graph(adjacency);
    DFS dfs(graph);         
    dfs.traverseGraph();

    auto& nodes = graph.getNodes();

    ASSERT_EQ(nodes.at(0)->getKey(), 'A');
    ASSERT_EQ(nodes.at(0)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(1)->getKey(), 'B');
    ASSERT_EQ(nodes.at(1)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(2)->getKey(), 'C');
    ASSERT_EQ(nodes.at(2)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(3)->getKey(), 'D');
    ASSERT_EQ(nodes.at(3)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(4)->getKey(), 'E');
    ASSERT_EQ(nodes.at(4)->getState(), State::COMPLETED);
}


TEST(runTestDFS, 2)
{
    std::vector<std::vector<char>> adjacency = { { 'A', 'B', 'D' },
                                                 { 'B', 'A', 'C', 'D', 'G' },
                                                 { 'C', 'B', 'G' },
                                                 { 'D', 'A', 'B', 'F' },
                                                 { 'E', 'F'},
                                                 { 'F', 'D', 'E' },
                                                 { 'G', 'B', 'C' } };
    Graph graph(adjacency);
    DFS dfs(graph);
    dfs.traverseGraph();

    auto& nodes = graph.getNodes();

    ASSERT_EQ(nodes.at(0)->getKey(), 'A');
    ASSERT_EQ(nodes.at(0)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(1)->getKey(), 'B');
    ASSERT_EQ(nodes.at(1)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(2)->getKey(), 'C');
    ASSERT_EQ(nodes.at(2)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(3)->getKey(), 'D');
    ASSERT_EQ(nodes.at(3)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(4)->getKey(), 'E');
    ASSERT_EQ(nodes.at(4)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(5)->getKey(), 'F');
    ASSERT_EQ(nodes.at(5)->getState(), State::COMPLETED);
    ASSERT_EQ(nodes.at(6)->getKey(), 'G');
    ASSERT_EQ(nodes.at(6)->getState(), State::COMPLETED);
}

