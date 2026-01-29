
#include "color.h"

#include <bits/stdc++.h>
#include <ranges>


Color::Color(Graph& graph) : graph{ graph } {}


void Color::colorGraph()
{
    graph.resetVisitFlags();
    graph.resetColors();

    for (uint8_t i = 1; i <= graph.getSize(); i++) {
        colorPool.insert({ i, false });
    }

    auto adjacency{ graph.getAdjacency() };
    if (graph.isDirected()) {
        extendAdjacency(adjacency);
    }

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

    if (adjacency.contains(key) == false) {
        return;
    }

    for (auto& [_, value] : colorPool) value = false;

    for (const auto& edge : adjacency.at(key)) {
        if (graph.isNodeVisited(edge.dst) == IsProperty::NO) {
            nodesQueue.push(edge.dst);
        }
        auto nodeColor = graph.getNodeColor(edge.dst);
        if (nodeColor) {
            colorPool.at(nodeColor) = true;
        }
    }

    for (const auto& [colorID, isUsed] : colorPool) {
        if (!isUsed) {
            graph.setNodeColor(key, colorID);
            break;
        }
    }
}


void Color::extendAdjacency(std::map<char, std::list<Edge>>& adjacency)
{
    for (auto& [key, edges] : adjacency) {
        for (auto& edge : edges) {
            if (!adjacency.contains(edge.dst)) {
                adjacency.insert(std::make_pair(edge.dst, std::list<Edge>{}));
            }
            auto& adjacencyDst = adjacency.at(edge.dst);
            if (std::ranges::find_if(adjacencyDst, [key](const auto& edge) { return edge.dst == key; }) == adjacencyDst.end()) {
                adjacencyDst.emplace_back(edge.dst, key, edge.weight);
            }
        }
    }
}

