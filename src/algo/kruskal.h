
#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include <list>
#include <memory>
#include <vector>

#include "graph/graph.h"
#include "graph/edge.h"


struct Tree
{
    Tree(char key, size_t treeID) : key{ key }, treeID{ treeID } {}
    const char key;
    size_t treeID;
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
    std::unique_ptr<std::vector<Tree>> createInitialTrees();

    Graph& graph;
};

#endif

