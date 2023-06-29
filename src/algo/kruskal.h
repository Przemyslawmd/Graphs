
#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include "../graph/graph.h"
#include "../graph/edge.h"

#include <list>
#include <memory>
#include <vector>


struct PartialTree {

    PartialTree(char key, int treeNumber) : key(key), treeNumber(treeNumber) {}
    char key;
    int treeNumber;
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

    std::list<Edge> sortEdges();
    std::vector<PartialTree> initializePartialTrees();

    Graph& graph;
};

#endif

