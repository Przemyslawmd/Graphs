
#include "kruskal.h"

#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>

constexpr int NOT_ATTACHED = 0;


Kruskal::Kruskal(GraphList& graph) : graph(graph) {}


std::unique_ptr<std::vector<Edge>> Kruskal::makeMinSpanningTree()
{
    auto sortedEdges = sortEdges();
    auto trees = initializePartialTrees();

    auto edges = std::make_unique<std::vector<Edge>>();
    int lastPartialTree = 0;

    while (sortedEdges->empty() == false) {

        if (std::find_if (trees->begin(), trees->end(), [](const auto& tree) { return tree.treeNumber != 1; })  == trees->end()) {
            break;
        }

        Edge edge = sortedEdges->back();
        sortedEdges->pop_back();

        auto srcEdge = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.src; });
        auto dstEdge = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.dst; });

        if (srcEdge->treeNumber == dstEdge->treeNumber && srcEdge->treeNumber != NOT_ATTACHED) {
            continue;
        }
        if (srcEdge->treeNumber == NOT_ATTACHED && dstEdge->treeNumber == NOT_ATTACHED) {
            lastPartialTree++;
            srcEdge->treeNumber = lastPartialTree;
            dstEdge->treeNumber = lastPartialTree;
        }
        else if (srcEdge->treeNumber == NOT_ATTACHED || dstEdge->treeNumber == NOT_ATTACHED) {
            if (srcEdge->treeNumber == NOT_ATTACHED) {
                srcEdge->treeNumber = dstEdge->treeNumber;
            }
            else {
                dstEdge->treeNumber = srcEdge->treeNumber;
            }
        }
        else {
            int numberExtended = srcEdge->treeNumber < dstEdge->treeNumber ? srcEdge->treeNumber : dstEdge->treeNumber;
            int numberDeleted = numberExtended == srcEdge->treeNumber ? dstEdge->treeNumber : srcEdge->treeNumber;
            for (auto& tree : *trees) {
                if (tree.treeNumber == numberDeleted) {
                    tree.treeNumber = numberExtended;
                }
            }
        }
        edges->push_back(edge);
    }
    return edges;
}


std::unique_ptr<std::list<Edge>> Kruskal::sortEdges()
{
    std::unique_ptr<std::list<Edge>> sortedEdges = std::make_unique<std::list<Edge>>();;
    for (auto& [key, edges] : graph.getAdjacency()) {
        for (auto& edge : edges) {
            auto iter = std::find_if(sortedEdges->begin(), sortedEdges->end(), 
                                     [&edge](auto& sortedEdge) { return sortedEdge.isEqual(edge); });
            if (iter == sortedEdges->end()) {
                sortedEdges->push_back(Edge{ edge.src, edge.dst, edge.weight });
            }
        }
    }
    sortedEdges->sort([](const Edge& edge1, const Edge& edge2) { return edge1.weight > edge2.weight; });
    return sortedEdges;
}


std::unique_ptr<std::vector<PartialTree>> Kruskal::initializePartialTrees()
{
    std::unique_ptr<std::vector<PartialTree>> trees = std::make_unique<std::vector<PartialTree>>();
    const auto& adjacency = graph.getAdjacency();
    trees->reserve(adjacency.size());
    for (const auto& [key, edges] : adjacency) {
        trees->push_back(PartialTree{ key, NOT_ATTACHED });
    }
    return trees;
}

