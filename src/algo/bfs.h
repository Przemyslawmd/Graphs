
#ifndef GRAPHS_BFS_H
#define GRAPHS_BFS_H

#include "../graph/edge.h"
#include "../graph/graph.h"

#include <queue>


class BFS
{
public:

    BFS(Graph&);
    BFS(const BFS&) = delete;
    BFS& operator=(BFS&) = delete;

    void traverseGraph();

private:

    void processQueue(const std::map<char, std::list<Edge>>& adjacency);

    Graph& graph;
    std::queue<char> nodesQueue;
};

#endif

