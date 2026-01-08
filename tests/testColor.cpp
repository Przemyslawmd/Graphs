
#include "baseTest.h"

#include "graphFactory.h"

#include "graph/graph.h"
#include "algo/color.h"


void checkNodesColors(const std::vector<Node>& nodes, const std::map<char, uint16_t>& expected)
{
    auto it = nodes.cbegin();
    for (const auto& [key, colorID] : expected) {
        auto it = std::find_if(nodes.begin(), nodes.end(), [&key](const auto& node) { return node.getKey() == key;});
        ASSERT_EQ(it->color, colorID);
    }
}


class ColorTest : public GraphTest {};


TEST_F(ColorTest, FirstTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FiveNodes);
    Color color{ graph };
    color.colorGraph();

    const std::map<char, uint16_t> expected = { {'a', 1 }, { 'b', 2 }, { 'c', 1 }, { 'd', 2 }, { 'e', 3 }};
    const auto& nodes = graph.getNodes();
    checkNodesColors(nodes, expected);
}


TEST_F(ColorTest, SecondTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_SevenNodes);
    Color color{ graph };
    color.colorGraph();

    const std::map<char, uint16_t> expected = 
        {{ 'a', 1 }, { 'b', 2 } , { 'c', 1 }, { 'd', 3 }, { 'e', 2 }, { 'f', 1 }, { 'g', 3 }};
    const auto& nodes = graph.getNodes();
    checkNodesColors(nodes, expected);
}

