
#include "../src/graph/graph.h"
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

    Graph graph(adjacency);
    auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes.at(0)->getKey(), 'A');
    ASSERT_EQ(nodes.at(1)->getKey(), 'B');
    ASSERT_EQ(nodes.at(2)->getKey(), 'C');
    ASSERT_EQ(nodes.at(3)->getKey(), 'D');
    ASSERT_EQ(nodes.at(4)->getKey(), 'E');
}

