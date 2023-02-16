
#include "../src/algo/dfs.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


TEST(TestDFS, 1)
{
    Graph graph;
    graph.addNodes({ 'A', 'B', 'C', 'D', 'E' });    

    graph.addEdges('A', { 'B' });
    graph.addEdges('B', { 'A', 'C' });
    graph.addEdges('C', { 'B', 'D', 'E' });
    graph.addEdges('D', { 'C', 'E' });
    graph.addEdges('E', { 'C', 'D' });

    DFS dfs(graph);
    dfs.traverseGraph();

    const auto& nodes = graph.getNodes();
		
    EXPECT_EQ(nodes[0]->getKey(), 'A');
    EXPECT_TRUE(nodes[0]->isVisited());
    EXPECT_EQ(nodes[1]->getKey(), 'B');
    EXPECT_TRUE(nodes[1]->isVisited());
    EXPECT_EQ(nodes[2]->getKey(), 'C');
    EXPECT_TRUE(nodes[2]->isVisited());
    EXPECT_EQ(nodes[3]->getKey(), 'D');
    EXPECT_TRUE(nodes[3]->isVisited());
    EXPECT_EQ(nodes[4]->getKey(), 'E');
    EXPECT_TRUE(nodes[4]->isVisited());
}    


TEST(TestDFS, 2)
{
    Graph graph;
    graph.addNodes({ 'A', 'B', 'C', 'D', 'E', 'F', 'G' });   

    graph.addEdges('A', { 'B', 'D' });
    graph.addEdges('B', { 'A', 'C', 'D', 'G' });
    graph.addEdges('C', { 'B', 'G' });
    graph.addEdges('D', { 'A', 'B', 'F' });
    graph.addEdges('E', { 'F' });
    graph.addEdges('F', { 'D', 'E' });
    graph.addEdges('G', { 'B', 'C' });

    DFS dfs(graph);
    dfs.traverseGraph();
    
    const auto& nodes = graph.getNodes();

    EXPECT_EQ(nodes[0]->getKey(), 'A');
    EXPECT_TRUE(nodes[0]->isVisited());
    EXPECT_EQ(nodes[1]->getKey(), 'B');
    EXPECT_TRUE(nodes[1]->isVisited());
    EXPECT_EQ(nodes[2]->getKey(), 'C');
    EXPECT_TRUE(nodes[2]->isVisited());
    EXPECT_EQ(nodes[3]->getKey(), 'D');
    EXPECT_TRUE(nodes[3]->isVisited());
    EXPECT_EQ(nodes[4]->getKey(), 'E');
    EXPECT_TRUE(nodes[4]->isVisited());
    EXPECT_EQ(nodes[5]->getKey(), 'F');
    EXPECT_TRUE(nodes[5]->isVisited());
    EXPECT_EQ(nodes[6]->getKey(), 'G');
    EXPECT_TRUE(nodes[6]->isVisited());
}

