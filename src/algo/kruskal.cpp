
#include "kruskal.h"

#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>

constexpr int NOT_ATTACHED = 0;


Kruskal::Kruskal(Graph& graph) : graph(graph) {}


std::unique_ptr<std::vector<Edge>> Kruskal::makeMinSpanningTree()
{
    auto sortedEdges = sortEdges();
    auto trees = initializePartialTrees();

    auto spanningTreeEdges = std::make_unique<std::vector<Edge>>();
    int lastPartialTree = 0;

    const auto& BothEdgesAttachedInTheSameTree = [] (int t_1, int t_2) { return t_1 == t_2 && t_1 != NOT_ATTACHED; };
    const auto& BothEdgesAttachedInDifferentTrees = [] (int t_1, int t_2) { return t_1 != t_2 && t_1 != NOT_ATTACHED && t_2 != NOT_ATTACHED; };
    const auto& BothEdgesNotAttached = [] (int t_1, int t_2) { return t_1 == NOT_ATTACHED && t_2 == NOT_ATTACHED; };

    while (sortedEdges->empty() == false) {

        if (std::find_if (trees->begin(), trees->end(), [](const auto& tree) { return tree.treeNumber != 1; }) == trees->end()) {
            break;
        }

        Edge edge = sortedEdges->back();
        sortedEdges->pop_back();

        auto srcEdge = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.src; });
        auto dstEdge = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.dst; });

        if (BothEdgesAttachedInTheSameTree(srcEdge->treeNumber, dstEdge->treeNumber)) {
            continue;
        }
        else if (BothEdgesNotAttached(srcEdge->treeNumber, dstEdge->treeNumber)) {
            lastPartialTree++;
            srcEdge->treeNumber = lastPartialTree;
            dstEdge->treeNumber = lastPartialTree;
        }
        else if (BothEdgesAttachedInDifferentTrees(srcEdge->treeNumber, dstEdge->treeNumber)) {
            int treeExtended = srcEdge->treeNumber < dstEdge->treeNumber ? srcEdge->treeNumber : dstEdge->treeNumber;
            int treeDeleted = treeExtended == srcEdge->treeNumber ? dstEdge->treeNumber : srcEdge->treeNumber;
            for (auto& tree : *trees) {
                if (tree.treeNumber == treeDeleted) {
                    tree.treeNumber = treeExtended;
                }
            }
        }
        else if (srcEdge->treeNumber == NOT_ATTACHED) {
            srcEdge->treeNumber = dstEdge->treeNumber;
        }
        else {
            dstEdge->treeNumber = srcEdge->treeNumber;
        }
        spanningTreeEdges->push_back(edge);
    }
    return spanningTreeEdges;
}


std::unique_ptr<std::list<Edge>> Kruskal::sortEdges()
{
    auto edgesToSort = std::make_unique<std::list<Edge>>();
    for (auto& [key, edges] : graph.getAdjacency()) {
        for (auto& edge : edges) {
            auto iter = std::find_if(edgesToSort->begin(), edgesToSort->end(), 
                                     [&edge](auto& edgeToSort) { return edgeToSort.isEqual(edge); });
            if (iter == edgesToSort->end()) {
                edgesToSort->push_back(Edge{ edge.src, edge.dst, edge.weight });
            }
        }
    }
    edgesToSort->sort([](const Edge& edge1, const Edge& edge2) { return edge1.weight > edge2.weight; });
    return edgesToSort;
}


std::unique_ptr<std::vector<PartialTree>> Kruskal::initializePartialTrees()
{
    auto trees = std::make_unique<std::vector<PartialTree>>();
    const auto& adjacency = graph.getAdjacency();
    trees->reserve(adjacency.size());
    for (const auto& [key, edges] : adjacency) {
        trees->push_back(PartialTree{ key, NOT_ATTACHED });
    }
    return trees;
}

