
#include "kruskal.h"

#include <algorithm>

constexpr int NOT_ATTACHED = 0;


Kruskal::Kruskal(Graph& graph) : graph(graph) {}


std::unique_ptr<std::vector<Edge>> Kruskal::makeMinSpanningTree()
{
    auto sortedEdges = sortEdges();
    auto trees = initializePartialTrees();

    auto spanningTreeEdges = std::make_unique<std::vector<Edge>>();
    spanningTreeEdges->reserve(sortedEdges->size());

    int highestPartialTree = 0;

    while (sortedEdges->empty() == false) {

        Edge edge = sortedEdges->back();
        sortedEdges->pop_back();

        auto src = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.src; });
        auto dst = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.dst; });

        if (src->treeNumber == dst->treeNumber && src->treeNumber != NOT_ATTACHED) {
            continue;
        }
        else if (src->treeNumber == NOT_ATTACHED && dst->treeNumber == NOT_ATTACHED) {
            highestPartialTree++;
            src->treeNumber = highestPartialTree;
            dst->treeNumber = highestPartialTree;
        }
        else if (src->treeNumber != dst->treeNumber && src->treeNumber != NOT_ATTACHED && dst->treeNumber != NOT_ATTACHED) {
            int toExtend = src->treeNumber < dst->treeNumber ? src->treeNumber : dst->treeNumber;
            int toDelete = toExtend == src->treeNumber ? dst->treeNumber : src->treeNumber;
            for (auto& tree : *trees) {
                if (tree.treeNumber == toDelete) {
                    tree.treeNumber = toExtend;
                }
            }
        }
        else if (src->treeNumber == NOT_ATTACHED) {
            src->treeNumber = dst->treeNumber;
        }
        else {
            dst->treeNumber = src->treeNumber;
        }
        spanningTreeEdges->push_back(edge);
    }
    return spanningTreeEdges;
}


std::unique_ptr<std::list<Edge>> Kruskal::sortEdges()
{
    auto sortedEdges = std::make_unique<std::list<Edge>>();
    for (auto& [key, edges] : graph.getAdjacency()) {
        for (auto& edge : edges) {
            if (std::all_of(sortedEdges->begin(), sortedEdges->end(), [&edge](auto& edgeToSort) { return !(edgeToSort == edge); })) {
                sortedEdges->push_back({ edge.src, edge.dst, edge.weight });
            }
        }
    }
    sortedEdges->sort([](const Edge& edge1, const Edge& edge2) { return edge1.weight > edge2.weight; });
    return sortedEdges;
}


std::unique_ptr<std::vector<PartialTree>> Kruskal::initializePartialTrees()
{
    auto trees = std::make_unique<std::vector<PartialTree>>();
    const auto& adjacency = graph.getAdjacency();
    trees->reserve(adjacency.size());
    for (const auto& [key, edges] : adjacency) {
        trees->push_back({ key, NOT_ATTACHED });
    }
    return trees;
}

