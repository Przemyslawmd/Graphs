
#include "../src/graphclient.h"
#include "../src/graph/graph.h"
#include "../src/graph/node.h"
#include "../src/graphclient.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>


TEST(TestClient, FindShortestPath)
{
    GraphClient client;
    client.addNodes({ 'a', 'b', 'c', 'd', 'e', 'f' });

    client.addEdgesWithWeight('a', {{ 'd', 5 }, { 'e', 2 }, { 'f', 8 }});
    client.addEdgesWithWeight('b', {{ 'a', 4 }, { 'c', 5 }});
    client.addEdgesWithWeight('d', {{ 'e', 2 }});
    client.addEdgesWithWeight('e', {{ 'b', 4 }, { 'c', 2 }, { 'f', 1 }});
    client.addEdgesWithWeight('f', {{ 'c', 6 }});

    std::unique_ptr<std::vector<char>> path = client.findShortestPath('a', 'b');

    ASSERT_EQ(path->size(), 3);
    ASSERT_EQ(path->at(0), 'a');
    ASSERT_EQ(path->at(1), 'e');
    ASSERT_EQ(path->at(2), 'b');

    path = client.findShortestPath('e', 'd');

    ASSERT_EQ(path->size(), 4);
    ASSERT_EQ(path->at(0), 'e');
    ASSERT_EQ(path->at(1), 'b');
    ASSERT_EQ(path->at(2), 'a');
    ASSERT_EQ(path->at(3), 'd');
}

