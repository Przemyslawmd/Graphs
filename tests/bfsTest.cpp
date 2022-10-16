
#include "../src/bfs/bfs.h"
#include "../src/graph/Node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


TEST(runTestBFS, 1)
{
    
    std::vector<std::vector<char>> adjacency = { { 'A', 'B' }, 
                                                 { 'B', 'A', 'C' }, 
                                                 { 'C', 'B', 'D', 'E'}, 
                                                 { 'D', 'C', 'E' },  
                                                 { 'E', 'C', 'D'} }; 
    
    Graph graph(adjacency);
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


TEST(runTestBFS, 2)
{

    std::vector<std::vector<char>> adjacency = { { 'A', 'B', 'D' }, 
                                                 { 'B', 'A', 'C', 'D', 'G' }, 
                                                 { 'C', 'B', 'G' }, 
                                                 { 'D', 'A', 'B', 'F' },  
                                                 { 'E', 'F'},
                                                 { 'F', 'D', 'E' },
                                                 { 'G', 'B', 'C' } }; 
    Graph graph(adjacency);
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

