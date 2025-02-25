
#include "kruskal.h"

#include <algorithm>
#include <ranges>

constexpr int NOT_ATTACHED = 0;


Kruskal::Kruskal(Graph& graph) : graph(graph) {}


std::unique_ptr<std::vector<Edge>> Kruskal::makeMinSpanningTree()
{
    auto sortedEdges = sortEdges();
    auto trees = initPartialTrees();

    auto spanningTree = std::make_unique<std::vector<Edge>>();
    spanningTree->reserve(sortedEdges->size());

    int lastPartialTree = 0;

    while (sortedEdges->empty() == false) {

        Edge edge = sortedEdges->back();
        sortedEdges->pop_back();

        auto src = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.src; });
        auto dst = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.dst; });

        if (src->tree != NOT_ATTACHED && src->tree == dst->tree) {
            continue;
        }

        if (src->tree == NOT_ATTACHED && dst->tree == NOT_ATTACHED) {
            lastPartialTree++;
            src->tree = lastPartialTree;
            dst->tree = lastPartialTree;
        }
        else if (src->tree == NOT_ATTACHED) {
            src->tree = dst->tree;
        }
        else if (src->tree != NOT_ATTACHED && dst->tree != NOT_ATTACHED && src->tree != dst->tree) {
            int toExtend = src->tree < dst->tree ? src->tree : dst->tree;
            int toDelete = toExtend == src->tree ? dst->tree : src->tree;
            for (auto& tree : *trees) {
                if (tree.tree == toDelete) {
                    tree.tree = toExtend;
                }
            }
        }
        else {
            dst->tree = src->tree;
        }
        spanningTree->push_back(std::move(edge));
    }
    return spanningTree;
}


std::unique_ptr<std::list<Edge>> Kruskal::sortEdges()
{
    auto sorted = std::make_unique<std::list<Edge>>();
    for (const auto& edges : graph.getAdjacency() | std::views::values) {
        for (const auto& edge : edges) {
            if (std::none_of(sorted->begin(), sorted->end(), [&edge](auto& e) { return e == edge; })) {
                sorted->emplace_back(edge.src, edge.dst, edge.weight);
            }
        }
    }
    sorted->sort([](const Edge& edge1, const Edge& edge2) { return edge1.weight > edge2.weight; });
    return sorted;
}


std::unique_ptr<std::vector<PartialTree>> Kruskal::initPartialTrees()
{
    auto trees = std::make_unique<std::vector<PartialTree>>();
    const auto& adjacency = graph.getAdjacency();
    trees->reserve(adjacency.size());
    for (const auto& key : adjacency | std::views::keys) {
        trees->emplace_back(key, NOT_ATTACHED);
    }
    return trees;
}

