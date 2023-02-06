
#ifndef GRAPHS_KRUSKAL_H
#define GRAPHS_KRUSKAL_H

#include "../graph/graphList.h"
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

    Kruskal(GraphList&);
    Kruskal(const Kruskal&) = delete;
    Kruskal& operator=(Kruskal&) = delete;

    std::unique_ptr<std::vector<Edge>> makeMinSpanningTree();

private:

    void sortEdges();
    void initializePartialTrees();

    std::list<Edge> sortedEdges;
    std::vector<PartialTree> trees;
    GraphList& graph;
};

#endif

