
#ifndef GRAPH_TEST_BASE_H
#define GRAPH_TEST_BASE_H

#include <chrono>

#include <gtest/gtest.h>

#include "timeType.h"
#include "../src/graph/node.h"


class GraphTest : public testing::Test
{
protected:

    void checkNodes(const std::vector<Node>& nodes, int expectedNodesCount)
    {
        ASSERT_EQ(nodes.size(), expectedNodesCount);
        for (auto& node : nodes) {
            EXPECT_TRUE(node.isVisited());
        }
    }

    void showDuration(const TIME_TYPE start, const TIME_TYPE end)
    {
        const char* testCase = ::testing::UnitTest::GetInstance()->current_test_info()->test_case_name();
        const char* testName = ::testing::UnitTest::GetInstance()->current_test_info()->name();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(20) << testCase << std::setw(12) << testName << " : time in microseconds : " << elapsed.count() << std::endl;
    }
};

#endif