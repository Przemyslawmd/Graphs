
#include "../src/graphclient.h"
#include "../src/graph/graph.h"
#include "../src/graph/node.h"
#include "../src/graphclient.h"

#include <gtest/gtest.h>

#include <memory>
#include <tuple>
#include <vector>


TEST(TestClient, FindShortestPath)
{
    GraphClient client;
    client.addNodes({ 'a', 'b', 'c', 'd', 'e', 'f' });

    client.addEdgesWeighted('a', {{ 'd', 5 }, { 'e', 2 }, { 'f', 8 }});
    client.addEdgesWeighted('b', {{ 'a', 4 }, { 'c', 5 }});
    client.addEdgesWeighted('d', {{ 'e', 2 }});
    client.addEdgesWeighted('e', {{ 'b', 4 }, { 'c', 2 }, { 'f', 1 }});
    client.addEdgesWeighted('f', {{ 'c', 6 }});

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


TEST(TestClient, FindMinSpanningTree)
{
    GraphClient client;
    client.addNodes({ 'a', 'b', 'c', 'd', 'e', 'f' });

    client.addEdgesWeighted('a', {{ 'b', 1 }, { 'c', 7 }});
    client.addEdgesWeighted('b', {{ 'a', 1 }, { 'c', 5 }, { 'd', 4 }});
    client.addEdgesWeighted('c', {{ 'a', 7 }, { 'e', 6 }});
    client.addEdgesWeighted('d', {{ 'e', 2 }, { 'b', 4 }});
    client.addEdgesWeighted('e', {{ 'b', 3 } });

    auto edges = client.findMinSpanningTree();

    ASSERT_EQ(edges->size(), 4);

    ASSERT_EQ(std::get<0>(edges->at(0)), 'a');
    ASSERT_EQ(std::get<1>(edges->at(0)), 'b');

    ASSERT_EQ(std::get<0>(edges->at(1)), 'd');
    ASSERT_EQ(std::get<1>(edges->at(1)), 'e');

    ASSERT_EQ(std::get<0>(edges->at(2)), 'e');
    ASSERT_EQ(std::get<1>(edges->at(2)), 'b');

    ASSERT_EQ(std::get<0>(edges->at(3)), 'b');
    ASSERT_EQ(std::get<1>(edges->at(3)), 'c');
}

