
#include "../src/bfs/bfs.h"
#include "../src/graph/Node.h"
#include "../src/graph/graphList.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


TEST(TestBFS, 1)
{
    GraphList graph;
    graph.addNodes({ 'A', 'B', 'C', 'D', 'E' });    

    graph.addEdge('A', 'B');
    graph.addEdges('B', { 'A', 'C' });
    graph.addEdges('C', { 'B', 'D', 'E' });
    graph.addEdges('D', { 'C', 'E' });
    graph.addEdges('E', { 'C', 'D' });

    BFS bfs;
    bfs.traverseGraph(graph);

    auto& nodes = graph.getNodes();
		
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


TEST(TestBFS, 2)
{
    GraphList graph;
    graph.addNodes({ 'A', 'B', 'C', 'D', 'E', 'F', 'G' });   

    graph.addEdges('A', { 'B', 'D' });
    graph.addEdges('B', { 'A', 'C', 'D', 'G' });
    graph.addEdges('C', { 'B', 'G' });
    graph.addEdges('D', { 'A', 'B', 'F' });
    graph.addEdge('E', 'F');
    graph.addEdges('F', { 'D', 'E' });
    graph.addEdges('G', { 'B', 'C' });

    BFS bfs;
    bfs.traverseGraph(graph);
    
    auto& nodes = graph.getNodes();

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

