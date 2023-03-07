
#include "../src/graph/edge.h"
#include "../src/graph/graph.h"
#include "../src/graph/node.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>
 

void checkAdjacency(const std::map<char, 
                    std::list<Edge>>& adjacency,
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


void checkAdjacencyWithWeight(const std::map<char, 
                              std::list<Edge>>& adjacency, 
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
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e' };
    Graph graph{ false, false };
    graph.addNodes(keys);

    graph.addEdges('a', { 'b' });
    graph.addEdges('b', { 'a', 'c' });
    graph.addEdges('c', { 'b', 'd', 'e' });
    graph.addEdges('d', { 'c', 'e' } );
    graph.addEdges('e', { 'c', 'd' });

    const auto& nodes = graph.getNodes();

    ASSERT_EQ(nodes[0]->key, 'a');
    ASSERT_EQ(nodes[1]->key, 'b');
    ASSERT_EQ(nodes[2]->key, 'c');
    ASSERT_EQ(nodes[3]->key, 'd');
    ASSERT_EQ(nodes[4]->key, 'e');

    const auto& adjacency = graph.getAdjacency();

    ASSERT_EQ(adjacency.size(), 5);
    for (char key : keys) {
        ASSERT_EQ(adjacency.count(key), 1);
    }

    checkAdjacency(adjacency, 'a', { 'b' });
    checkAdjacency(adjacency, 'b', { 'a', 'c' });
    checkAdjacency(adjacency, 'c', { 'b', 'd', 'e' });
    checkAdjacency(adjacency, 'd', { 'c', 'e' });
    checkAdjacency(adjacency, 'e', { 'c', 'd' });
}


TEST(TestCreateGraph, SecondTestImproperEdges)
{
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e' };
    Graph graph{ false, false };
    graph.addNodes(keys);

    graph.addEdges('a', { 'b' });
    graph.addEdges('b', { 'a', 'c' });
    graph.addEdges('c', { 'b', 'd', 'e' });
    graph.addEdges('a', { 'b' });                // repeat edge
    graph.addEdges('d', { 'c', 'e' });
    graph.addEdges('F', { 'e' });                // improper source key
    graph.addEdges('e', { 'c', 'd'});
    graph.addEdges('d', { 'G' });                // improper destination key

    const auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->key, 'a');
    ASSERT_EQ(nodes[1]->key, 'b');
    ASSERT_EQ(nodes[2]->key, 'c');
    ASSERT_EQ(nodes[3]->key, 'd');
    ASSERT_EQ(nodes[4]->key, 'e');

    const auto& adjacency = graph.getAdjacency();

    ASSERT_EQ(adjacency.size(), 7);
    for (char key : keys) {
        ASSERT_EQ(adjacency.count(key), 1);    
    }
    
    checkAdjacency(adjacency, 'a', { 'b' });
    checkAdjacency(adjacency, 'b', { 'a', 'c' });
    checkAdjacency(adjacency, 'c', { 'b', 'd', 'e' });
    checkAdjacency(adjacency, 'd', { 'c', 'e', 'G' });
    checkAdjacency(adjacency, 'e', { 'c', 'd', 'F' });
}


TEST(TestCreateGraph, ThirdTestGraphWithWeights)
{
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e' };
    Graph graph{ true, true };
    graph.addNodes(keys);

    graph.addEdgesWeighted('a', {{ 'b', 1  }});
    graph.addEdgesWeighted('b', {{ 'a', 2  }, { 'c', 4   }});
    graph.addEdgesWeighted('c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 }});
    graph.addEdgesWeighted('d', {{ 'c', 5  }, { 'e', 12  }});
    graph.addEdgesWeighted('e', {{ 'c', 3  }, { 'd', 101 }});

    const auto& nodes = graph.getNodes();
    
    ASSERT_EQ(nodes[0]->key, 'a');
    ASSERT_EQ(nodes[1]->key, 'b');
    ASSERT_EQ(nodes[2]->key, 'c');
    ASSERT_EQ(nodes[3]->key, 'd');
    ASSERT_EQ(nodes[4]->key, 'e');

    const auto& adjacency = graph.getAdjacency();

    ASSERT_EQ(adjacency.size(), 5);
    for (char key : keys) {
        ASSERT_EQ(adjacency.count(key), 1);
    }

    checkAdjacencyWithWeight(adjacency, 'a', {{ 'b', 1  }});
    checkAdjacencyWithWeight(adjacency, 'b', {{ 'a', 2  }, { 'c', 4   }});
    checkAdjacencyWithWeight(adjacency, 'c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 }});
    checkAdjacencyWithWeight(adjacency, 'd', {{ 'c', 5  }, { 'e', 12  }});
    checkAdjacencyWithWeight(adjacency, 'e', {{ 'c', 3  }, { 'd', 101 }});
}

