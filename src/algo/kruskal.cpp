
#include "kruskal.h"

#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>


Kruskal::Kruskal(GraphList& graph) : graph(graph) {}


std::unique_ptr<GraphList> Kruskal::makeMinSpanningTree()
{
    return nullptr;
}


void Kruskal::sortEdges()
{
    for (auto& [key, edges] : graph.getAdjacency()) {
        for (auto& edge : edges) {
            auto iter = std::find_if(sortedEdges.begin(), sortedEdges.end(), [&edge](auto& sortedEdge) { return sortedEdge.isEqual(edge); });
            if (iter == sortedEdges.end()) {
                sortedEdges.push_back(Edge{ edge.src, edge.dst, edge.weight });
            }
        }
    }

    sortedEdges.sort([](const Edge& edge1, const Edge& edge2) { return edge1.weight < edge2.weight; });
}

