
#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include <list>
#include <memory>
#include <vector>

#include "graph/graph.h"
#include "graph/edge.h"


struct PartialTree {

    PartialTree(char key, size_t tree) : key(key), tree(tree) {}
    const char key;
    size_t tree;
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

    std::unique_ptr<std::list<Edge>> createSortedEdges();
    std::unique_ptr<std::vector<PartialTree>> createPartialTrees();

    Graph& graph;
};

#endif

