
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


TEST_F(ColorTest, TwoConnectedDiamonds)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::TwoConnectedDiamonds);
    Color color{ graph };
    color.colorGraph();

    const std::map<char, uint16_t> expected = 
        {{ 'a', 1 }, { 'b', 2 } , { 'c', 1 }, { 'd', 3 }, { 'e', 2 }, { 'f', 1 }, { 'g', 3 }, {'h', 1 }};
    const auto& nodes = graph.getNodes();
    checkNodesColors(nodes, expected);
}


TEST_F(ColorTest, SixteenNodesA)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::SixteenNodes_A);
    Color color{ graph };
    color.colorGraph();

    const std::map<char, uint16_t> expected = 
        {{ 'a', 1 }, { 'b', 2 }, { 'c', 3 }, { 'd', 1 }, { 'e', 2 }, { 'f', 3 }, { 'g', 3 }, { 'h', 4 },
         { 'i', 4 }, { 'j', 2 }, { 'k', 5 }, { 'l', 6 }, { 'm', 6 }, { 'n', 1 }, { 'o', 5 }, { 'p', 4 }};
    const auto& nodes = graph.getNodes();
    checkNodesColors(nodes, expected);
}


TEST_F(ColorTest, SixteenNodesB)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::SixteenNodes_B);
    Color color{ graph };
    color.colorGraph();

    const std::map<char, uint16_t> expected = 
        {{ 'a', 1 }, { 'b', 2 }, { 'c', 3 }, { 'd', 1 }, { 'e', 3 }, { 'f', 1 }, { 'g', 3 }, { 'h', 3 },
         { 'i', 2 }, { 'j', 2 }, { 'k', 1 }, { 'l', 2 }, { 'm', 5 }, { 'n', 1 }, { 'o', 4 }, { 'p', 5 }};
    const auto& nodes = graph.getNodes();
    checkNodesColors(nodes, expected);
}


TEST_F(ColorTest, SixteenNodesC)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::SixteenNodes_C);
    Color color{ graph };
    color.colorGraph();

    const std::map<char, uint16_t> expected = 
        {{ 'a', 1 }, { 'b', 2 }, { 'c', 2 }, { 'd', 1 }, { 'e', 2 }, { 'f', 1 }, { 'g', 3 }, { 'h', 3 },
         { 'i', 1 }, { 'j', 3 }, { 'k', 3 }, { 'l', 2 }, { 'm', 2 }, { 'n', 1 }, { 'o', 4 }, { 'p', 2 }};
    const auto& nodes = graph.getNodes();
    checkNodesColors(nodes, expected);
}

