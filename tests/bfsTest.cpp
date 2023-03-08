
#include "../src/algo/bfs.h"
#include "../src/graph/node.h"
#include "../src/graph/graph.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


class BFSTest : public ::testing::Test
{
protected:

    void checkNodes(const std::vector<std::unique_ptr<Node>>& nodes,
                    const std::vector<char>& keys)
    {
        ASSERT_EQ(nodes.size(), keys.size());

        auto it = nodes.cbegin();
        for (const auto key : keys) {
            EXPECT_EQ(key, (*it)->key);
            EXPECT_TRUE((*it)->isVisited());
            std::advance(it, 1);
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
    checkNodes(nodes, { 'a', 'b', 'c', 'd', 'e' });
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
    checkNodes(nodes, { 'a', 'b', 'd', 'c', 'g', 'f', 'e' });
}

