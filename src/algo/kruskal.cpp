
#include "kruskal.h"

#include <algorithm>
#include <ranges>

constexpr size_t NOT_ATTACHED = 0;


Kruskal::Kruskal(Graph& graph) : graph{ graph } {}


std::unique_ptr<std::vector<Edge>> Kruskal::makeMinSpanningTree()
{
    auto sortedEdges = createSortedEdges();
    auto trees = createInitialTrees();

    auto spanningTree = std::make_unique<std::vector<Edge>>();
    spanningTree->reserve(sortedEdges->size());
    size_t lastTreeID = 0;

    while (sortedEdges->empty() == false) {

        Edge edge = sortedEdges->back();
        sortedEdges->pop_back();

        auto src = std::ranges::find_if(*trees, [&edge](const auto& tree) { return tree.key == edge.src; });
        auto dst = std::ranges::find_if(*trees, [&edge](const auto& tree) { return tree.key == edge.dst; });

        if (src->treeID && src->treeID == dst->treeID) {
            continue;
        }

        if (src->treeID == NOT_ATTACHED && dst->treeID == NOT_ATTACHED) {
            lastTreeID++;
            src->treeID = lastTreeID;
            dst->treeID = lastTreeID;
        }
        else if (src->treeID == NOT_ATTACHED) {
            src->treeID = dst->treeID;
        }
        else if (src->treeID && dst->treeID && src->treeID != dst->treeID) {
            size_t toExtend = src->treeID < dst->treeID ? src->treeID : dst->treeID;
            size_t toDelete = toExtend == src->treeID ? dst->treeID : src->treeID;
            for (auto& tree : *trees) {
                if (tree.treeID == toDelete) {
                    tree.treeID = toExtend;
                }
            }
        }
        else {
            dst->treeID = src->treeID;
        }
        spanningTree->push_back(std::move(edge));
    }
    return spanningTree;
}


std::unique_ptr<std::list<Edge>> Kruskal::createSortedEdges()
{
    auto sortedEdges = std::make_unique<std::list<Edge>>();
    for (const auto& edges : graph.getAdjacency() | std::views::values) {
        for (const auto& edge : edges) {
            if (std::none_of(sortedEdges->begin(), sortedEdges->end(), [&edge](auto& e) { return e == edge; })) {
                sortedEdges->emplace_back(edge.src, edge.dst, edge.weight);
            }
        }
    }
    sortedEdges->sort([](const Edge& edge1, const Edge& edge2) { return edge1.weight > edge2.weight; });
    return sortedEdges;
}


std::unique_ptr<std::vector<Tree>> Kruskal::createInitialTrees()
{
    auto trees = std::make_unique<std::vector<Tree>>();
    const auto& adjacency = graph.getAdjacency();
    trees->reserve(adjacency.size());
    for (const auto& key : adjacency | std::views::keys) {
        trees->emplace_back(key, NOT_ATTACHED);
    }
    return trees;
}

