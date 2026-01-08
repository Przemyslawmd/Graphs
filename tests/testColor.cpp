
#include "baseTest.h"

#include "graphFactory.h"

#include "graph/graph.h"
#include "algo/color.h"


class ColorTest : public GraphTest {};


TEST_F(ColorTest, FirstTest)
{
    Graph graph{ false };
    GraphFactory::createGraph(graph, GraphType::Unweighted_FiveNodes);
    Color color{ graph };
    color.colorGraph('a');

    const std::vector<uint16_t> expectedColors = { 0, 1, 0, 1, 2 };
    const auto& nodes = graph.getNodes();

    auto it = nodes.cbegin();
    for (const auto colorID : expectedColors) {
        ASSERT_EQ(colorID, it->colour.value());
        std::advance(it, 1);
    }
}


