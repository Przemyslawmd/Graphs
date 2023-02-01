
#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include "../graph/graphList.h"

#include <memory>


class Kruskal
{
public:

    Kruskal(GraphList&);
    Kruskal(const Kruskal&) = delete;
    Kruskal& operator=(Kruskal&) = delete;

    std::unique_ptr<GraphList> makeMinSpanningTree();

private:

    GraphList& graph;

}

#endif

