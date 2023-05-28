
#include "../src/algo/bfs.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


class BFSTest : public ::testing::Test
{
protected:

    void checkNodes(const std::vector<std::unique_ptr<Node>>& nodes, int expectedNodesCount)
    {
        ASSERT_EQ(nodes.size(), expectedNodesCount);
        for (auto& node : nodes) {
            EXPECT_TRUE(node->isVisited());
        }
    }
};


TEST_F(BFSTest, FirstTest)
{
    Graph graph{ false, false };

    graph.addEdges('a', { 'b' });
    graph.addEdges('b', { 'a', 'c' });
    graph.addEdges('c', { 'b', 'd', 'e' });
    graph.addEdges('d', { 'c', 'e' });
    graph.addEdges('e', { 'c', 'd' });

    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 5);
}


TEST_F(BFSTest, SecondTest)
{
    Graph graph{ false, false };

    graph.addEdges('a', { 'b', 'd' });
    graph.addEdges('b', { 'a', 'c', 'd', 'g' });
    graph.addEdges('c', { 'b', 'g' });
    graph.addEdges('d', { 'a', 'b', 'f' });
    graph.addEdges('e', { 'f' });
    graph.addEdges('f', { 'd', 'e' });
    graph.addEdges('g', { 'b', 'c' });

    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 7);
}


TEST_F(BFSTest, ThirdTest)
{
    Graph graph{ true, false };

    graph.addEdges('a', { 'd', 'h' });
    graph.addEdges('b', { 'c' });
    graph.addEdges('c', { 'a', 'i' });
    graph.addEdges('d', { 'b', 'e', 'f' });
    graph.addEdges('e', { 'c' });
    graph.addEdges('f', { 'e', 'h', 'k'});
    graph.addEdges('g', { 'e', 'i' });
    graph.addEdges('h', { 'g', 'j' });
    graph.addEdges('i', { 'f', 'n'});
    graph.addEdges('j', { 'k' });
    graph.addEdges('k', { 'l' });
    graph.addEdges('l', { 'c', 'n' });
    graph.addEdges('m', { 'h', 'k'});
    graph.addEdges('n', { 'm' });

    BFS bfs{ graph };
    bfs.traverseGraph();

    const auto& nodes = graph.getNodes();
    checkNodes(nodes, 14) ;
}

