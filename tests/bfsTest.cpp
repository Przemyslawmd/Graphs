
#include "../src/bfs/bfs.h"
#include "../src/graph/Node.h"
#include "../src/graph/graphList.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


TEST(runTestBFS, 1)
{
    GraphList graph;
    graph.addNodes(std::vector<char> { 'A', 'B', 'C', 'D', 'E' });    

    graph.addEdge('A', 'B');
    graph.addEdge('B', 'A');
    graph.addEdge('B', 'C');
    graph.addEdge('C', 'B');
    graph.addEdge('C', 'D');
    graph.addEdge('C', 'E');
    graph.addEdge('D', 'C');
    graph.addEdge('D', 'E');
    graph.addEdge('E', 'C');
    graph.addEdge('E', 'D');

    BFS bfs;
    bfs.traverseGraph(graph);

	auto& nodes = graph.getNodes();
		
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_TRUE(nodes[0]->isVisited());
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_TRUE(nodes[1]->isVisited());
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_TRUE(nodes[2]->isVisited());
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_TRUE(nodes[3]->isVisited());
    ASSERT_EQ(nodes[4]->getKey(), 'E');
    ASSERT_TRUE(nodes[4]->isVisited());
}    


TEST(runTestBFS, 4)
{
    GraphList graph;
    graph.addNodes(std::vector<char> { 'A', 'B', 'C', 'D', 'E', 'F', 'G' });   

    graph.addEdge('A', 'B');
    graph.addEdge('A', 'D');
    graph.addEdge('B', 'A');
    graph.addEdge('B', 'C');
    graph.addEdge('B', 'D');
    graph.addEdge('B', 'G');
    graph.addEdge('C', 'B');
    graph.addEdge('C', 'G');
    graph.addEdge('D', 'A');
    graph.addEdge('D', 'B');
    graph.addEdge('D', 'F');
    graph.addEdge('E', 'F');
    graph.addEdge('F', 'D');
    graph.addEdge('F', 'E');
    graph.addEdge('G', 'B');
    graph.addEdge('G', 'C');

    BFS bfs;
    bfs.traverseGraph(graph);
    
    auto& nodes = graph.getNodes();

    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_TRUE(nodes[0]->isVisited());
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_TRUE(nodes[1]->isVisited());
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_TRUE(nodes[2]->isVisited());
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_TRUE(nodes[3]->isVisited());
    ASSERT_EQ(nodes[4]->getKey(), 'E');
    ASSERT_TRUE(nodes[4]->isVisited());
    ASSERT_EQ(nodes[5]->getKey(), 'F');
    ASSERT_TRUE(nodes[5]->isVisited());
    ASSERT_EQ(nodes[6]->getKey(), 'G');
    ASSERT_TRUE(nodes[6]->isVisited());
}

