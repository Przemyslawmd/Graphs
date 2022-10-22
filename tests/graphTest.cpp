
#include "../src/graph/graph.h"
#include "../src/graph/graphList.h"
#include "../src/graph/node.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>
    

void checkAdjacency(std::map<char, std::list<std::tuple<char, int>>>& adjacency, char key, std::vector<char>& neighbours)
{
    ASSERT_EQ(adjacency[key].size(), neighbours.size());
    
    auto it = adjacency[key].begin();
    for (char neighbour : neighbours) {
        ASSERT_EQ(std::get<0>(*it), neighbour);
        std::advance(it, 1);
    }
}


TEST(runTestCreateGraph, 1)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D', 'E' }; 
    GraphList graph;
    graph.addNodes(keys);

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

    auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_EQ(nodes[4]->getKey(), 'E');

    auto& adjacency = graph.getAdjacency();

    ASSERT_EQ(adjacency.size(), 5);
    ASSERT_EQ(adjacency.count('A'), 1);
    ASSERT_EQ(adjacency.count('B'), 1);
    ASSERT_EQ(adjacency.count('C'), 1);
    ASSERT_EQ(adjacency.count('D'), 1);
    ASSERT_EQ(adjacency.count('E'), 1);

    checkAdjacency(adjacency, 'A', std::vector<char> { 'B' });
    checkAdjacency(adjacency, 'B', std::vector<char> { 'A', 'C' });
    checkAdjacency(adjacency, 'C', std::vector<char> { 'B', 'D', 'E' });
    checkAdjacency(adjacency, 'D', std::vector<char> { 'C', 'E' });
    checkAdjacency(adjacency, 'E', std::vector<char> { 'C', 'D' });
}


TEST(runTestCreateGraph, 2)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D', 'E' }; 
    GraphList graph;
    graph.addNodes(keys);

    graph.addEdge('A', 'B');
    graph.addEdge('B', 'A');
    graph.addEdge('B', 'C');
    graph.addEdge('C', 'B');
    graph.addEdge('C', 'D');
    graph.addEdge('C', 'E');
    // repeat edge
    graph.addEdge('A', 'B');
    graph.addEdge('D', 'C');
    graph.addEdge('D', 'E');
    // improper source key
    graph.addEdge('F', 'E');
    graph.addEdge('E', 'C');
    graph.addEdge('E', 'D');
    // improper destination key
    graph.addEdge('D', 'G');

    auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_EQ(nodes[4]->getKey(), 'E');

    auto& adjacency = graph.getAdjacency();

    ASSERT_EQ(adjacency.size(), 5);
    ASSERT_EQ(adjacency.count('A'), 1);
    ASSERT_EQ(adjacency.count('B'), 1);
    ASSERT_EQ(adjacency.count('C'), 1);
    ASSERT_EQ(adjacency.count('D'), 1);
    ASSERT_EQ(adjacency.count('E'), 1);

    checkAdjacency(adjacency, 'A', std::vector<char> { 'B' });
    checkAdjacency(adjacency, 'B', std::vector<char> { 'A', 'C' });
    checkAdjacency(adjacency, 'C', std::vector<char> { 'B', 'D', 'E' });
    checkAdjacency(adjacency, 'D', std::vector<char> { 'C', 'E' });
    checkAdjacency(adjacency, 'E', std::vector<char> { 'C', 'D' });
}

