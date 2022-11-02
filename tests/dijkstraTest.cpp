
#include "../src/algo/bfs.h"
#include "../src/graph/Node.h"
#include "../src/graph/graphList.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


TEST(TestDijkstra, FirstTest)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' }; 
    GraphList graph;
    graph.addNodes(keys);

    graph.addEdgesWithWeight('A', {{ 'B', 1 }, { 'D', 3 }});
    graph.addEdgesWithWeight('B', {{ 'C', 5 }, { 'D', 2 }, { 'E', 3 }});
    graph.addEdgesWithWeight('C', {{ 'E', 4 }, { 'F', 1 }});
    graph.addEdgesWithWeight('D', {{ 'G', 4 }});
    graph.addEdgesWithWeight('E', {{ 'D', 1 }, { 'G', 2 }});
    graph.addEdgesWithWeight('G', {{ 'F', 1 }});

    const auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_EQ(nodes[4]->getKey(), 'E');
    ASSERT_EQ(nodes[5]->getKey(), 'F');
    ASSERT_EQ(nodes[6]->getKey(), 'G');


    auto& adjacency = graph.getAdjacency();
}

