
#ifndef GRAPHS_BFS_H
#define GRAPHS_BFS_H

#include "../graph/edge.h"
#include "../graph/node.h"
#include "../graph/graphList.h"
#include "../graph/graphMatrix.h"

#include <queue>


class BFS
{
public:

    BFS(GraphList&);
    BFS(const BFS&) = delete;
    BFS& operator=(BFS&) = delete;

    void traverseGraph();

private:

    void processQueue(const std::map<char, std::list<Edge>>& adjacency);

    GraphList& graph;
    std::queue<char> nodesQueue;
};

#endif

