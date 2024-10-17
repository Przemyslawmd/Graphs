
#include "kruskal.h"

#include <algorithm>


constexpr int NOT_ATTACHED = 0;


Kruskal::Kruskal(Graph& graph) : graph(graph) {}


std::unique_ptr<std::vector<Edge>> Kruskal::makeMinSpanningTree()
{
    auto sortedEdges = createSortedEdges();
    auto trees = createPartialTrees();

    auto spanningTree = std::make_unique<std::vector<Edge>>();
    spanningTree->reserve(sortedEdges->size());

    int lastPartialTree = 0;

    while (sortedEdges->empty() == false) {

        Edge edge = sortedEdges->back();
        sortedEdges->pop_back();

        auto src = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.src; });
        auto dst = std::find_if(trees->begin(), trees->end(), [&edge](const auto& tree) { return tree.key == edge.dst; });

        if (src->number == dst->number && src->number != NOT_ATTACHED) {
            continue;
        }
        else if (src->number == NOT_ATTACHED && dst->number == NOT_ATTACHED) {
            lastPartialTree++;
            src->number = lastPartialTree;
            dst->number = lastPartialTree;
        }
        else if (src->number != dst->number && src->number != NOT_ATTACHED && dst->number != NOT_ATTACHED) {
            int toExtend = src->number < dst->number ? src->number : dst->number;
            int toDelete = toExtend == src->number ? dst->number : src->number;
            for (auto& tree : *trees) {
                if (tree.number == toDelete) {
                    tree.number = toExtend;
                }
            }
        }
        else if (src->number == NOT_ATTACHED) {
            src->number = dst->number;
        }
        else {
            dst->number = src->number;
        }
        spanningTree->push_back(std::move(edge));
    }
    return spanningTree;
}


std::unique_ptr<std::list<Edge>> Kruskal::createSortedEdges()
{
    auto sortedEdges = std::make_unique<std::list<Edge>>();
    for (const auto& [key, edges] : graph.getAdjacency()) {
        for (const auto& edge : edges) {
            if (std::all_of(sortedEdges->begin(), sortedEdges->end(), [&edge](auto& edgeToSort) { return !(edgeToSort == edge); })) {
                sortedEdges->push_back({ edge.src, edge.dst, edge.weight });
            }
        }
    }
    sortedEdges->sort([](const Edge& edge1, const Edge& edge2) { return edge1.weight > edge2.weight; });
    return sortedEdges;
}


std::unique_ptr<std::vector<PartialTree>> Kruskal::createPartialTrees()
{
    auto trees = std::make_unique<std::vector<PartialTree>>();
    const auto& adjacency = graph.getAdjacency();
    trees->reserve(adjacency.size());
    for (const auto& [key, _] : adjacency) {
        trees->emplace_back(key, NOT_ATTACHED);
    }
    return trees;
}

