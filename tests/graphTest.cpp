
#include "../src/graph/edge.h"
#include "../src/graph/graph.h"
#include "../src/graph/node.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>
 

void checkAdjacency(const std::map<char, std::list<Edge>>& adjacency,
                    char key,
                    const std::vector<char>& neighboursVec)
{
    ASSERT_EQ(adjacency.at(key).size(), neighboursVec.size());
    
    auto it = adjacency.at(key).begin();
    for (char neighbour : neighboursVec) {
        EXPECT_EQ(it->dst, neighbour);
        std::advance(it, 1);
    }
}


void checkAdjacencyWithWeight(const std::map<char, std::list<Edge>>& adjacency, 
                              char key,
                              const std::vector<std::tuple<char, int>>& edgesVec)
{
    ASSERT_EQ(adjacency.at(key).size(), edgesVec.size());
    
    auto it = adjacency.at(key).begin();
    for (const auto& edge : edgesVec) {
        EXPECT_EQ(it->dst, std::get<0>(edge));
        EXPECT_EQ(it->weight, std::get<1>(edge));
        std::advance(it, 1);
    }
}


TEST(TestCreateGraph, FirstTest)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D', 'E' }; 
    Graph graph;
    graph.addNodes(keys);

    graph.addEdges('A', { 'B' });
    graph.addEdges('B', { 'A', 'C' });
    graph.addEdges('C', { 'B', 'D', 'E' });
    graph.addEdges('D', { 'C', 'E' } );
    graph.addEdges('E', { 'C', 'D' });

    const auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_EQ(nodes[4]->getKey(), 'E');

    const auto& adjacency = graph.getAdjacency();

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


TEST(TestCreateGraph, SecondTestImproperEdges)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D', 'E' }; 
    Graph graph;
    graph.addNodes(keys);

    graph.addEdges('A', { 'B' });
    graph.addEdges('B', { 'A', 'C' });
    graph.addEdges('C', { 'B', 'D', 'E' });
    graph.addEdges('A', { 'B' });                // repeat edge
    graph.addEdges('D', { 'C', 'E' });
    graph.addEdges('F', { 'E' });                // improper source key
    graph.addEdges('E', { 'C', 'D'});
    graph.addEdges('D', { 'G' });                // improper destination key

    const auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_EQ(nodes[4]->getKey(), 'E');

    const auto& adjacency = graph.getAdjacency();

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


TEST(TestCreateGraph, ThirdTestGraphWithWeights)
{
    std::vector<char> keys = { 'A', 'B', 'C', 'D', 'E' }; 
    Graph graph;
    graph.addNodes(keys);

    graph.addEdgesWithWeight('A', {{ 'B', 1  }});
    graph.addEdgesWithWeight('B', {{ 'A', 2  }, { 'C', 4   }});
    graph.addEdgesWithWeight('C', {{ 'B', 10 }, { 'D', 4   }, { 'E', 1 }});
    graph.addEdgesWithWeight('D', {{ 'C', 5  }, { 'E', 12  }});
    graph.addEdgesWithWeight('E', {{ 'C', 3  }, { 'D', 101 }});

    const auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->getKey(), 'A');
    ASSERT_EQ(nodes[1]->getKey(), 'B');
    ASSERT_EQ(nodes[2]->getKey(), 'C');
    ASSERT_EQ(nodes[3]->getKey(), 'D');
    ASSERT_EQ(nodes[4]->getKey(), 'E');

    const auto& adjacency = graph.getAdjacency();

    ASSERT_EQ(adjacency.size(), 5);
    for (char key : keys) {
        ASSERT_EQ(adjacency.count(key), 1);    
    }

    checkAdjacencyWithWeight(adjacency, 'A', {{ 'B', 1  }});
    checkAdjacencyWithWeight(adjacency, 'B', {{ 'A', 2  }, { 'C', 4   }});
    checkAdjacencyWithWeight(adjacency, 'C', {{ 'B', 10 }, { 'D', 4   }, { 'E', 1 }});
    checkAdjacencyWithWeight(adjacency, 'D', {{ 'C', 5  }, { 'E', 12  }});
    checkAdjacencyWithWeight(adjacency, 'E', {{ 'C', 3  }, { 'D', 101 }});
}

