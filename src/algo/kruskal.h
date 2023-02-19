
#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include "../graph/graph.h"
#include "../graph/edge.h"

#include <list>
#include <memory>
#include <vector>


typedef struct {
    char key;
    int treeNumber;
} PartialTree;


class Kruskal
{
public:

    explicit Kruskal(Graph&);
    Kruskal(const Kruskal&) = delete;
    Kruskal& operator=(Kruskal&) = delete;

    std::unique_ptr<std::vector<Edge>> makeMinSpanningTree();

private:

    std::unique_ptr<std::list<Edge>> sortEdges();
    std::unique_ptr<std::vector<PartialTree>> initializePartialTrees();

    Graph& graph;
};

#endif

