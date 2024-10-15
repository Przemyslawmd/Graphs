
#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include "../graph/graph.h"
#include "../graph/edge.h"

#include <list>
#include <memory>
#include <vector>


struct PartialTree
{
    PartialTree(char key, size_t number) : key(key), number(number) {}
    const char key;
    size_t number;
};


class Kruskal
{
public:

    explicit Kruskal(Graph&);
    Kruskal(const Kruskal&) = delete;
    Kruskal(Kruskal&&) = delete;
    Kruskal& operator=(const Kruskal&) = delete;
    Kruskal& operator=(Kruskal&&) = delete;

    std::unique_ptr<std::vector<Edge>> makeMinSpanningTree();

private:

    std::list<Edge> createSortedEdges();
    std::vector<PartialTree> createPartialTrees();

    Graph& graph;
};

#endif

