
#include "color.h"

#include <bits/stdc++.h>

Color::Color(Graph& graph) : graph(graph) {}


void Color::colorGraph()
{
    graph.resetVisitFlags();
    graph.resetColors();

    for (uint16_t i = 1; i <= graph.getSize(); i++) {
        colorPool.insert({ i, false });
    }

    const auto& adjacency = graph.getAdjacency();
    nodesQueue.push(adjacency.begin()->first);

    while (nodesQueue.empty() == false) {
        processQueue(adjacency);
        nodesQueue.pop();
    }
}


void Color::processQueue(const std::map<char, std::list<Edge>>& adjacency)
{
    const char key = nodesQueue.front();
    graph.setNodeAsVisited(key);

    for (auto& [_, value] : colorPool) value = false;

    if (adjacency.contains(key) == false) {
        return;
    }

    for (const auto& edge : adjacency.at(key)) {
        if (graph.isNodeVisited(edge.dst) == IsProperty::NO) {
            nodesQueue.push(edge.dst);
        }
        auto nodeColor = graph.getNodeColor(edge.dst);
        if (nodeColor) {
            colorPool.at(nodeColor) = true;
        }
    }

    for (const auto& [colorID, value] : colorPool) {
        if (value == false) {
            graph.setNodeColor(key, colorID);
            break;
        }
    }
}

