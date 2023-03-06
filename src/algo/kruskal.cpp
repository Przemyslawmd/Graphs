
#include "kruskal.h"

#include <algorithm>

constexpr int NOT_ATTACHED = 0;


Kruskal::Kruskal(Graph& graph) : graph(graph) {}


std::unique_ptr<std::vector<Edge>> Kruskal::makeMinSpanningTree()
{
    auto sortedEdges = sortEdges();
    auto trees = initializePartialTrees();

    auto spanningTreeEdges = std::make_unique<std::vector<Edge>>();
    int lastPartialTree = 0;

    const auto& isAttached = [] (int tree) { return tree != NOT_ATTACHED; };

    while (sortedEdges->empty() == false) {

        if (std::all_of(trees->begin(), trees->end(), [](const auto& tree) { return tree.treeNumber == 1; })) {
            break;
        }

        Edge edge = sortedEdges->back();
        sortedEdges->pop_back();

        auto src = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.src; });
        auto dst = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.dst; });

        if (src->treeNumber == dst->treeNumber && isAttached(src->treeNumber)) {
            continue;
        }
        else if (isAttached(src->treeNumber) == false && isAttached(dst->treeNumber) == false) {
            lastPartialTree++;
            src->treeNumber = lastPartialTree;
            dst->treeNumber = lastPartialTree;
        }
        else if (src->treeNumber != dst->treeNumber && isAttached(src->treeNumber) && isAttached(dst->treeNumber)) {
            int treeExtended = src->treeNumber < dst->treeNumber ? src->treeNumber : dst->treeNumber;
            int treeDeleted = treeExtended == src->treeNumber ? dst->treeNumber : src->treeNumber;
            for (auto& tree : *trees) {
                if (tree.treeNumber == treeDeleted) {
                    tree.treeNumber = treeExtended;
                }
            }
        }
        else if (isAttached(src->treeNumber) == false) {
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
    auto edgesToSort = std::make_unique<std::list<Edge>>();
    for (auto& [key, edges] : graph.getAdjacency()) {
        for (auto& edge : edges) {
            if (std::all_of(edgesToSort->begin(), edgesToSort->end(), [&edge](auto& edgeToSort) { return !(edgeToSort == edge); })) {
                edgesToSort->push_back({ edge.src, edge.dst, edge.weight });
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
        trees->push_back({ key, NOT_ATTACHED });
    }
    return trees;
}

