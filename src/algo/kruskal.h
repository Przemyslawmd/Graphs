
#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include "../graph/graphList.h"
#include "../graph/edge.h"

#include <memory>


class Kruskal
{
public:

    Kruskal(GraphList&);
    Kruskal(const Kruskal&) = delete;
    Kruskal& operator=(Kruskal&) = delete;

    std::unique_ptr<GraphList> makeMinSpanningTree();

    void sortEdges();

    std::list<Edge> sortedEdges;
    GraphList& graph;
};

#endif

