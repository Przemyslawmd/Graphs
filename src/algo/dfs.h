
#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include "../graph/graph.h"


class DFS
{
public:

    explicit DFS(Graph&);
    DFS(const DFS&) = delete;
    DFS(DFS&&) = delete;
    DFS& operator=(const DFS&) = delete;
    DFS& operator=(DFS&&) = delete;


    void traverseGraph();

private:

    void processNode(char key);

    Graph& graph;
};

#endif

