
#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include "../graph/graphList.h"


class DFS
{
public:

    DFS(GraphList&);
    DFS(const DFS&) = delete;
    DFS& operator=(DFS&) = delete;

    void traverseGraph();

private:

    void processNode(char key);

    GraphList& graph;
};

#endif

