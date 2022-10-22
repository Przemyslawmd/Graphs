
#include "../src/graph/graph.h"
#include "../src/graph/graphList.h"
#include "../src/graph/node.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>
    

void checkAdjacency(std::map<char, std::list<std::tuple<char, int>>>& adjacency, char key, const std::vector<char>& neighbours)
{
    ASSERT_EQ(adjacency[key].size(), neighbours.size());
    
    auto it = adjacency[key].begin();
    for (char neighbour : neighbours) {
        EXPECT_EQ(std::get<0>(*it), neighbour);
        std::advance(it, 1);
    }
}


TEST(TestCreateGraph, 1)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D', 'E' }; 
    GraphList graph;
    graph.addNodes(keys);

    graph.addEdge('A', 'B');
    graph.addEdges('B', { 'A', 'C' });
    graph.addEdges('C', { 'B', 'D', 'E' });
    graph.addEdges('D', { 'C', 'E' } );
    graph.addEdges('E', { 'C', 'D' });

    auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_EQ(nodes[4]->getKey(), 'E');

    auto& adjacency = graph.getAdjacency();

    ASSERT_EQ(adjacency.size(), 5);
    for (char key : keys) {
        ASSERT_EQ(adjacency.count(key), 1);    
    }

    checkAdjacency(adjacency, 'A', { 'B' });
    checkAdjacency(adjacency, 'B', { 'A', 'C' });
    checkAdjacency(adjacency, 'C', { 'B', 'D', 'E' });
    checkAdjacency(adjacency, 'D', { 'C', 'E' });
    checkAdjacency(adjacency, 'E', { 'C', 'D' });
}


TEST(TestCreateGraph, 2)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D', 'E' }; 
    GraphList graph;
    graph.addNodes(keys);

    graph.addEdge('A', 'B');
    graph.addEdges('B', { 'A', 'C' });
    graph.addEdges('C', { 'B', 'D', 'E' });
    graph.addEdge('A', 'B');                // repeat edge
    graph.addEdges('D', { 'C', 'E' } );
    graph.addEdge('F', 'E');                // improper source key
    graph.addEdges('E', {'C', 'D'});
    graph.addEdge('D', 'G');                // improper destination key

    auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_EQ(nodes[4]->getKey(), 'E');

    auto& adjacency = graph.getAdjacency();

    ASSERT_EQ(adjacency.size(), 5);
    for (char key : keys) {
        ASSERT_EQ(adjacency.count(key), 1);    
    }
    
    checkAdjacency(adjacency, 'A', { 'B' });
    checkAdjacency(adjacency, 'B', { 'A', 'C' });
    checkAdjacency(adjacency, 'C', { 'B', 'D', 'E' });
    checkAdjacency(adjacency, 'D', { 'C', 'E' });
    checkAdjacency(adjacency, 'E', { 'C', 'D' });
}

