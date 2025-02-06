
#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "../src/graph/edge.h"
#include "../src/graph/graph.h"
#include "../src/graph/node.h"


void checkAdjacency(const std::map<char, std::list<Edge>>& adjacency,
                    char key,
                    const std::vector<char>& neighbours)
{
    ASSERT_EQ(adjacency.at(key).size(), neighbours.size());

    auto it = adjacency.at(key).cbegin();
    for (char neighbour : neighbours) {
        EXPECT_EQ(it->dst, neighbour);
        std::advance(it, 1);
    }
}


void checkAdjacencyWithWeight(const std::map<char, std::list<Edge>>& adjacency,
                              char key,
                              const std::vector<std::tuple<char, int>>& edges)
{
    ASSERT_EQ(adjacency.at(key).size(), edges.size());

    auto it = adjacency.at(key).cbegin();
    for (const auto& edge : edges) {
        EXPECT_EQ(it->dst, std::get<0>(edge));
        EXPECT_EQ(it->weight, std::get<1>(edge));
        std::advance(it, 1);
    }
}


void checkNodes(const std::vector<Node>& nodes,
                const std::vector<char>& keys)
{
    ASSERT_EQ(nodes.size(), keys.size());

    auto it = nodes.cbegin();
    for (const auto key : keys) {
        EXPECT_EQ(key, (*it).key);
        std::advance(it, 1);
    }
}


TEST(TestCreateGraph, FirstTest)
{
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e' };
    Graph graph{ false };
    graph.addNodes(keys);

    graph.addEdges('a', { 'b' });
    graph.addEdges('b', { 'a', 'c' });
    graph.addEdges('c', { 'b', 'd', 'e' });
    graph.addEdges('d', { 'c', 'e' } );
    graph.addEdges('e', { 'c', 'd' });

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, { 'a', 'b', 'c', 'd', 'e' });

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 5);
    checkAdjacency(adjacency, 'a', { 'b' });
    checkAdjacency(adjacency, 'b', { 'a', 'c' });
    checkAdjacency(adjacency, 'c', { 'b', 'd', 'e' });
    checkAdjacency(adjacency, 'd', { 'c', 'e' });
    checkAdjacency(adjacency, 'e', { 'c', 'd' });
}


TEST(TestCreateGraph, SecondTestNoNodesCreatedBefore)
{
    Graph graph{ false };

    graph.addEdges('a', { 'b' });
    graph.addEdges('b', { 'a', 'c' });
    graph.addEdges('c', { 'b', 'd', 'e' });
    graph.addEdges('a', { 'b' });                // repeated edge
    graph.addEdges('d', { 'c', 'e' });
    graph.addEdges('f', { 'e' });
    graph.addEdges('e', { 'c', 'd'});
    graph.addEdges('d', { 'g' });

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, { 'a', 'b', 'c', 'd', 'e', 'f', 'g' });
    
    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 7);
    checkAdjacency(adjacency, 'a', { 'b' });
    checkAdjacency(adjacency, 'b', { 'a', 'c' });
    checkAdjacency(adjacency, 'c', { 'b', 'd', 'e' });
    checkAdjacency(adjacency, 'd', { 'c', 'e', 'g' });
    checkAdjacency(adjacency, 'e', { 'c', 'd', 'f' });
}


TEST(TestCreateGraph, ThirdTestGraphWithWeights)
{
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e' };
    Graph graph{ true };
    graph.addNodes(keys);

    graph.addEdgesWeighted('a', {{ 'b', 1  }});
    graph.addEdgesWeighted('b', {{ 'a', 2  }, { 'c', 4   }});
    graph.addEdgesWeighted('c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 }});
    graph.addEdgesWeighted('d', {{ 'c', 5  }, { 'e', 12  }});
    graph.addEdgesWeighted('e', {{ 'c', 3  }, { 'd', 101 }});

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, { 'a', 'b', 'c', 'd', 'e' });

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 5);
    checkAdjacencyWithWeight(adjacency, 'a', {{ 'b', 1  }});
    checkAdjacencyWithWeight(adjacency, 'b', {{ 'a', 2  }, { 'c', 4   }});
    checkAdjacencyWithWeight(adjacency, 'c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 }});
    checkAdjacencyWithWeight(adjacency, 'd', {{ 'c', 5  }, { 'e', 12  }});
    checkAdjacencyWithWeight(adjacency, 'e', {{ 'c', 3  }, { 'd', 101 }});
}

