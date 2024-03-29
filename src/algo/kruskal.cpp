
#include "kruskal.h"

#include <algorithm>

constexpr int NOT_ATTACHED = 0;


Kruskal::Kruskal(Graph& graph) : graph(graph) {}


std::unique_ptr<std::vector<Edge>> Kruskal::makeMinSpanningTree()
{
    auto sortedEdges = sortEdges();
    auto trees = initializePartialTrees();

    auto spanningTree = std::make_unique<std::vector<Edge>>();
    spanningTree->reserve(sortedEdges.size());

    int lastPartialTree = 0;

    while (sortedEdges.empty() == false) {

        Edge edge = sortedEdges.back();
        sortedEdges.pop_back();

        auto src = std::find_if(trees.begin(), trees.end(), [&edge](const auto& tree) { return tree.key == edge.src; });
        auto dst = std::find_if(trees.begin(), trees.end(), [&edge](const auto& tree) { return tree.key == edge.dst; });

        if (src->treeNumber == dst->treeNumber && src->treeNumber != NOT_ATTACHED) {
            continue;
        }
        else if (src->treeNumber == NOT_ATTACHED && dst->treeNumber == NOT_ATTACHED) {
            lastPartialTree++;
            src->treeNumber = lastPartialTree;
            dst->treeNumber = lastPartialTree;
        }
        else if (src->treeNumber != dst->treeNumber && src->treeNumber != NOT_ATTACHED && dst->treeNumber != NOT_ATTACHED) {
            int toExtend = src->treeNumber < dst->treeNumber ? src->treeNumber : dst->treeNumber;
            int toDelete = toExtend == src->treeNumber ? dst->treeNumber : src->treeNumber;
            for (auto& tree : trees) {
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
        spanningTree->push_back(std::move(edge));
    }
    return spanningTree;
}


std::list<Edge> Kruskal::sortEdges()
{
    std::list<Edge> sortedEdges;
    for (const auto& [key, edges] : graph.getAdjacency()) {
        for (const auto& edge : edges) {
            if (std::all_of(sortedEdges.begin(), sortedEdges.end(), [&edge](auto& edgeToSort) { return !(edgeToSort == edge); })) {
                sortedEdges.push_back({ edge.src, edge.dst, edge.weight });
            }
        }
    }
    sortedEdges.sort([](const Edge& edge1, const Edge& edge2) { return edge1.weight > edge2.weight; });
    return sortedEdges;
}


std::vector<PartialTree> Kruskal::initializePartialTrees()
{
    std::vector<PartialTree> trees;
    const auto& adjacency = graph.getAdjacency();
    trees.reserve(adjacency.size());
    for (const auto& [key, _] : adjacency) {
        trees.emplace_back(key, NOT_ATTACHED);
    }
    return trees;
}

