
#include <chrono>
#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "../src/algo/bfs.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"
#include "baseTest.h"
#include "graphFactory.h"


class BFSTest : public GraphTest {};


TEST_F(BFSTest, FirstTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FiveNodes);
    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 5);
}


TEST_F(BFSTest, SecondTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_SevenNodes);
    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 7);
}


TEST_F(BFSTest, ThirdTest)
{
    Graph graph{ true };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FourteenNodes);

    const auto begin = std::chrono::high_resolution_clock::now();
    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 14) ;
}


TEST_F(BFSTest, FourthTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_TwentyNodes);

    const auto begin = std::chrono::high_resolution_clock::now();
    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto end = std::chrono::high_resolution_clock::now();
    showDuration(begin, end);

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 20);
}

