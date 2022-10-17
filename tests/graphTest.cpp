
#include "../src/graph/graph.h"
#include "../src/graph/graphList.h"
#include "../src/graph/node.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>
    

TEST(runTestCreateGraph, 1)
{
    std::vector<std::vector<char>> adjacency = { { 'A', 'B' }, 
                                                 { 'B', 'A', 'C' }, 
                                                 { 'C', 'B', 'D', 'E'}, 
                                                 { 'D', 'C', 'E' },  
                                                 { 'E', 'C', 'D'} }; 

    GraphList graph(adjacency);
    auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_EQ(nodes[4]->getKey(), 'E');
}

