
#include "../src/algo/bfs.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


TEST(TestBFS, FirstTest)
{
    Graph graph{ false, false };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e' });

    graph.addEdges('a', { 'b' });
    graph.addEdges('b', { 'a', 'c' });
    graph.addEdges('c', { 'b', 'd', 'e' });
    graph.addEdges('d', { 'c', 'e' });
    graph.addEdges('e', { 'c', 'd' });

    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto& nodes = graph.getNodes();
		
    EXPECT_EQ(nodes[0]->getKey(), 'a');
    EXPECT_TRUE(nodes[0]->isVisited());
    EXPECT_EQ(nodes[1]->getKey(), 'b');
    EXPECT_TRUE(nodes[1]->isVisited());
    EXPECT_EQ(nodes[2]->getKey(), 'c');
    EXPECT_TRUE(nodes[2]->isVisited());
    EXPECT_EQ(nodes[3]->getKey(), 'd');
    EXPECT_TRUE(nodes[3]->isVisited());
    EXPECT_EQ(nodes[4]->getKey(), 'e');
    EXPECT_TRUE(nodes[4]->isVisited());
}


TEST(TestBFS, 2)
{
    Graph graph{ false, false };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e', 'f', 'g' });

    graph.addEdges('a', { 'b', 'd' });
    graph.addEdges('b', { 'a', 'c', 'd', 'g' });
    graph.addEdges('c', { 'b', 'g' });
    graph.addEdges('d', { 'a', 'b', 'f' });
    graph.addEdges('e', { 'f' });
    graph.addEdges('f', { 'd', 'e' });
    graph.addEdges('g', { 'b', 'c' });

    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto& nodes = graph.getNodes();

    EXPECT_EQ(nodes[0]->getKey(), 'a');
    EXPECT_TRUE(nodes[0]->isVisited());
    EXPECT_EQ(nodes[1]->getKey(), 'b');
    EXPECT_TRUE(nodes[1]->isVisited());
    EXPECT_EQ(nodes[2]->getKey(), 'c');
    EXPECT_TRUE(nodes[2]->isVisited());
    EXPECT_EQ(nodes[3]->getKey(), 'd');
    EXPECT_TRUE(nodes[3]->isVisited());
    EXPECT_EQ(nodes[4]->getKey(), 'e');
    EXPECT_TRUE(nodes[4]->isVisited());
    EXPECT_EQ(nodes[5]->getKey(), 'f');
    EXPECT_TRUE(nodes[5]->isVisited());
    EXPECT_EQ(nodes[6]->getKey(), 'g');
    EXPECT_TRUE(nodes[6]->isVisited());
}

