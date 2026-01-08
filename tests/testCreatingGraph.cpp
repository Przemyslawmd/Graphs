
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
        ASSERT_EQ(it->dst, neighbour);
        ASSERT_EQ(it->weight, 1);
        std::advance(it, 1);
    }
}


void checkAdjacencyWeighted(const std::list<Edge>& adjacency, const std::vector<std::tuple<char, size_t>>& expected)
{
    ASSERT_EQ(adjacency.size(), expected.size());

    auto it = adjacency.cbegin();
    for (const auto& edge : expected) {
        ASSERT_EQ(it->dst, std::get<char>(edge));
        ASSERT_EQ(it->weight, std::get<size_t>(edge));
        std::advance(it, 1);
    }
}


void checkNodes(const std::vector<Node>& nodes, const std::vector<char>& expectedKeys)
{
    ASSERT_EQ(nodes.size(), expectedKeys.size());

    auto it = nodes.cbegin();
    for (const auto key : expectedKeys) {
        ASSERT_EQ(key, it->getKey());
        std::advance(it, 1);
    }
}


TEST(TestCreateGraph, CommonTest)
{
    Graph graph{ false };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e' });

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


TEST(TestCreateGraph, NodesNotCreatedBefore)
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


TEST(TestCreateGraph, WeightedGraph)
{
    Graph graph{ true };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e' });

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


TEST(TestCreateGraph, RemoveNodes_1)
{
    Graph graph{ true };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e' });

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


TEST(TestCreateGraph, RemoveNodes_2)
{
    Graph graph{ true };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e' });

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


TEST(TestCreateGraph, RemoveEdge)
{
    Graph graph{ true };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e' });

    graph.addEdgesWeighted('a', {{ 'b', 1  }});
    graph.addEdgesWeighted('b', {{ 'a', 2  }, { 'c', 4   }});
    graph.addEdgesWeighted('c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 } });
    graph.addEdgesWeighted('d', {{ 'c', 5  }, { 'e', 12  }});
    graph.addEdgesWeighted('e', {{ 'c', 3  }, { 'd', 101 }});

    graph.removeEdge('c', 'e');

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 5);
    checkAdjacencyWeighted(adjacency.at('a'), {{ 'b', 1 }});
    checkAdjacencyWeighted(adjacency.at('b'), {{ 'a', 2  }, { 'c', 4   }});
    checkAdjacencyWeighted(adjacency.at('c'), {{ 'b', 10 }, { 'd', 4   }});
    checkAdjacencyWeighted(adjacency.at('d'), {{ 'c', 5  }, { 'e', 12  }});
    checkAdjacencyWeighted(adjacency.at('e'), {{ 'c', 3  }, { 'd', 101 }});
}


TEST(TestCreateGraph, RemoveAllEdgesFromNode)
{
    Graph graph{ true };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e' });

    graph.addEdgesWeighted('a', {{ 'b', 1  }});
    graph.addEdgesWeighted('b', {{ 'a', 2  }, { 'c', 4   } });
    graph.addEdgesWeighted('c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 } });
    graph.addEdgesWeighted('d', {{ 'c', 5  }, { 'e', 12  } });
    graph.addEdgesWeighted('e', {{ 'c', 3  }, { 'd', 101 } });

    graph.removeEdge('b', 'a');
    graph.removeEdge('b', 'c');

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 4);
    checkAdjacencyWeighted(adjacency.at('a'), {{ 'b', 1   }});
    checkAdjacencyWeighted(adjacency.at('c'), {{ 'b', 10 }, { 'd', 4 }, { 'e', 1 }});
    checkAdjacencyWeighted(adjacency.at('d'), {{ 'c', 5  }, { 'e', 12 }});
    checkAdjacencyWeighted(adjacency.at('e'), {{ 'c', 3  }, { 'd', 101 }});
}


TEST(TestCreateGraph, RemoveAndAddEdge)
{
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e' };
    Graph graph{ true };
    graph.addNodes(keys);

    graph.addEdgesWeighted('a', {{ 'b', 1  }});
    graph.addEdgesWeighted('b', {{ 'a', 2  }, { 'c', 4   }});
    graph.addEdgesWeighted('c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 } });
    graph.addEdgesWeighted('d', {{ 'c', 5  }, { 'e', 12  }});
    graph.addEdgesWeighted('e', {{ 'c', 3  }, { 'd', 101 }});

    graph.removeEdge('c', 'e');
    graph.addEdgeWeighted('c', 'e', 12);

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 5);
    checkAdjacencyWeighted(adjacency.at('a'), {{ 'b', 1   }});
    checkAdjacencyWeighted(adjacency.at('b'), {{ 'a', 2  }, { 'c', 4   }});
    checkAdjacencyWeighted(adjacency.at('c'), {{ 'b', 10 }, { 'd', 4   }, { 'e', 12 }});
    checkAdjacencyWeighted(adjacency.at('d'), {{ 'c', 5  }, { 'e', 12  }});
    checkAdjacencyWeighted(adjacency.at('e'), {{ 'c', 3  }, { 'd', 101 }});
}


TEST(TestCreateGraph, RemoveAllEdgesFromNodeAndAdd)
{
    std::vector<char> keys = { 'a', 'b', 'c', 'd', 'e' };
    Graph graph{ true };
    graph.addNodes(keys);

    graph.addEdgesWeighted('a', {{ 'b', 1  }});
    graph.addEdgesWeighted('b', {{ 'a', 2  }, { 'c', 4   }});
    graph.addEdgesWeighted('c', {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 } });
    graph.addEdgesWeighted('d', {{ 'c', 5  }, { 'e', 12  }});
    graph.addEdgesWeighted('e', {{ 'c', 3  }, { 'd', 101 }});

    graph.removeEdge('b', 'a');
    graph.removeEdge('b', 'c');

    graph.addEdgeWeighted('b', 'c', 10);
    graph.addEdgeWeighted('b', 'e', 2);

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 5);
    checkAdjacencyWeighted(adjacency.at('a'), {{ 'b', 1 } });
    checkAdjacencyWeighted(adjacency.at('b'), {{ 'c', 10 }, { 'e', 2   }});
    checkAdjacencyWeighted(adjacency.at('c'), {{ 'b', 10 }, { 'd', 4   }, { 'e', 1 }});
    checkAdjacencyWeighted(adjacency.at('d'), {{ 'c', 5  }, { 'e', 12  }});
    checkAdjacencyWeighted(adjacency.at('e'), {{ 'c', 3  }, { 'd', 101 }});
}


TEST(TestCreateGraph, RemoveEdgeUndirected)
{
    Graph graph{ false };
    graph.addNodes({ 'a', 'b', 'c', 'd', 'e' });

    graph.addEdgesWeighted('a', {{ 'b', 1 }, { 'c', 3 }});
    graph.addEdgesWeighted('b', {{ 'c', 4 }});
    graph.addEdgesWeighted('c', {{ 'd', 4 }, { 'e', 1 }});
    graph.addEdgesWeighted('d', {{ 'e', 12 }});

    graph.removeEdge('c', 'e');

    const auto& adjacency = graph.getAdjacency();
    ASSERT_EQ(adjacency.size(), 5);
    checkAdjacencyWeighted(adjacency.at('a'), {{ 'b', 1 }, { 'c', 3 }});
    checkAdjacencyWeighted(adjacency.at('b'), {{ 'a', 1 }, { 'c', 4 }});
    checkAdjacencyWeighted(adjacency.at('c'), {{ 'a', 3 }, { 'b', 4 }, { 'd', 4 }});
    checkAdjacencyWeighted(adjacency.at('d'), {{ 'c', 4 }, { 'e', 12 }});
    checkAdjacencyWeighted(adjacency.at('e'), {{ 'd', 12 }});
}

