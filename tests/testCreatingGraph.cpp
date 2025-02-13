
#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "graph/edge.h"
#include "graph/graph.h"
#include "graph/node.h"


void checkAdjacency(const std::list<Edge>& edges, const std::vector<char>& expected)
{
    ASSERT_EQ(edges.size(), expected.size());

    auto it = edges.cbegin();
    for (char neighbour : expected) {
        EXPECT_EQ(it->dst, neighbour);
        EXPECT_EQ(it->weight, 1);
        std::advance(it, 1);
    }
}


void checkAdjacencyWeighted(const std::list<Edge>& adjacency, const std::vector<std::tuple<char, size_t>>& expected)
{
    ASSERT_EQ(adjacency.size(), expected.size());

    auto it = adjacency.cbegin();
    for (const auto& edge : expected) {
        EXPECT_EQ(it->dst, std::get<0>(edge));
        EXPECT_EQ(it->weight, std::get<1>(edge));
        std::advance(it, 1);
    }
}


void checkNodes(const std::vector<Node>& nodes, const std::vector<char>& expectedKeys)
{
    ASSERT_EQ(nodes.size(), expectedKeys.size());

    auto it = nodes.cbegin();
    for (const auto key : expectedKeys) {
        ASSERT_EQ(key, it->key);
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
    checkAdjacency(adjacency.at('a'), { 'b' });
    checkAdjacency(adjacency.at('b'), { 'a', 'c' });
    checkAdjacency(adjacency.at('c'), { 'b', 'd', 'e' });
    checkAdjacency(adjacency.at('d'), { 'c', 'e' });
    checkAdjacency(adjacency.at('e'), { 'c', 'd' });
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
    graph.addEdges('e', { 'c', 'd' });
    graph.addEdges('d', { 'g' });

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, { 'a', 'b', 'c', 'd', 'e', 'f', 'g' });

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 7);
    checkAdjacency(adjacency.at('a'), { 'b' });
    checkAdjacency(adjacency.at('b'), { 'a', 'c' });
    checkAdjacency(adjacency.at('c'), { 'b', 'd', 'e' });
    checkAdjacency(adjacency.at('d'), { 'c', 'e', 'g' });
    checkAdjacency(adjacency.at('e'), { 'c', 'd', 'f' });
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
    checkAdjacencyWeighted(adjacency.at('a'), {{ 'b', 1  }});
    checkAdjacencyWeighted(adjacency.at('b'), {{ 'a', 2  }, { 'c', 4   }});
    checkAdjacencyWeighted(adjacency.at('c'), {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 }});
    checkAdjacencyWeighted(adjacency.at('d'), {{ 'c', 5  }, { 'e', 12  }});
    checkAdjacencyWeighted(adjacency.at('e'), {{ 'c', 3  }, { 'd', 101 }});
}


TEST(TestCreateGraph, RemovingNodesFirst)
{
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e' };
    Graph graph{ true };
    graph.addNodes(keys);

    graph.addEdgesWeighted('a', {{ 'b', 1  }});
    graph.addEdgesWeighted('b', {{ 'a', 2  }, { 'c', 4   }});
    graph.addEdgesWeighted('c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 }});
    graph.addEdgesWeighted('d', {{ 'c', 5  }, { 'e', 12  }});
    graph.addEdgesWeighted('e', {{ 'c', 3  }, { 'd', 101 }});

    graph.removeNode('c');

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 4);
    checkAdjacencyWeighted(adjacency.at('a'), {{ 'b', 1   }});
    checkAdjacencyWeighted(adjacency.at('b'), {{ 'a', 2   }});
    checkAdjacencyWeighted(adjacency.at('d'), {{ 'e', 12  }});
    checkAdjacencyWeighted(adjacency.at('e'), {{ 'd', 101 }});
}


TEST(TestCreateGraph, RemovingNodesSecond)
{
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e' };
    Graph graph{ true };
    graph.addNodes(keys);

    graph.addEdgesWeighted('a', {{ 'b', 1  }});
    graph.addEdgesWeighted('b', {{ 'a', 2  }, { 'c', 4   }});
    graph.addEdgesWeighted('c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 }});
    graph.addEdgesWeighted('d', {{ 'c', 5  }, { 'e', 12  }});
    graph.addEdgesWeighted('e', {{ 'c', 3  }, { 'd', 101 }});

    graph.removeNode('a');
    graph.removeNode('d');

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 3);
    checkAdjacencyWeighted(adjacency.at('b'), {{ 'c', 4  }});
    checkAdjacencyWeighted(adjacency.at('c'), {{ 'b', 10 }, { 'e', 1 }});
    checkAdjacencyWeighted(adjacency.at('e'), {{ 'c', 3  }});
}

