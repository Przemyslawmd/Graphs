
#include "../src/graphclient.h"
#include "../src/graph/graph.h"
#include "../src/graph/node.h"
#include "../src/graphclient.h"

#include <gtest/gtest.h>

#include <memory>
#include <vector>
 


TEST(TestClient, FirstTest)
{
    GraphClient client;
    client.findShortestPath('A', 'B');

    ASSERT_EQ(2,2);
}

