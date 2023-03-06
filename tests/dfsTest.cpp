
#include "../src/algo/dfs.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


TEST(TestDFS, 1)
{
    Graph graph{ false, false };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e' });

    graph.addEdges('a', { 'b' });
    graph.addEdges('b', { 'a', 'c' });
    graph.addEdges('c', { 'b', 'd', 'e' });
    graph.addEdges('d', { 'c', 'e' });
    graph.addEdges('e', { 'c', 'd' });

    DFS dfs{ graph };
    dfs.traverseGraph();

    const auto& nodes = graph.getNodes();

    EXPECT_EQ(nodes[0]->key, 'a');
    EXPECT_TRUE(nodes[0]->isVisited());
    EXPECT_EQ(nodes[1]->key, 'b');
    EXPECT_TRUE(nodes[1]->isVisited());
    EXPECT_EQ(nodes[2]->key, 'c');
    EXPECT_TRUE(nodes[2]->isVisited());
    EXPECT_EQ(nodes[3]->key, 'd');
    EXPECT_TRUE(nodes[3]->isVisited());
    EXPECT_EQ(nodes[4]->key, 'e');
    EXPECT_TRUE(nodes[4]->isVisited());
}    


TEST(TestDFS, 2)
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

    DFS dfs{ graph };
    dfs.traverseGraph();
    
    const auto& nodes = graph.getNodes();

    EXPECT_EQ(nodes[0]->key, 'a');
    EXPECT_TRUE(nodes[0]->isVisited());
    EXPECT_EQ(nodes[1]->key, 'b');
    EXPECT_TRUE(nodes[1]->isVisited());
    EXPECT_EQ(nodes[2]->key, 'c');
    EXPECT_TRUE(nodes[2]->isVisited());
    EXPECT_EQ(nodes[3]->key, 'd');
    EXPECT_TRUE(nodes[3]->isVisited());
    EXPECT_EQ(nodes[4]->key, 'e');
    EXPECT_TRUE(nodes[4]->isVisited());
    EXPECT_EQ(nodes[5]->key, 'f');
    EXPECT_TRUE(nodes[5]->isVisited());
    EXPECT_EQ(nodes[6]->key, 'g');
    EXPECT_TRUE(nodes[6]->isVisited());
}

