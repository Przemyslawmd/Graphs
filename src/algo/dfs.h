
#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include "../graph/graph.h"


class DFS
{
public:

    DFS(Graph&);
    DFS(const DFS&) = delete;
    DFS& operator=(DFS&) = delete;

    void traverseGraph();

private:

    void processNode(char key);

    Graph& graph;
};

#endif

