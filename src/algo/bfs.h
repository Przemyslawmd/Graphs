
#ifndef GRAPHS_BFS_H
#define GRAPHS_BFS_H

#include <list>
#include <map>
#include <memory>
#include <queue>

#include "graph/edge.h"
#include "graph/graph.h"


class BFS
{
public:

    explicit BFS(Graph&);
    BFS(const BFS&) = delete;
    BFS(BFS&&) = delete;
    BFS& operator=(const BFS&) = delete;
    BFS& operator=(BFS&&) = delete;

    std::unique_ptr<std::vector<char>> traverseGraph(char key);

private:

    void processQueue(const std::map<char, std::list<Edge>>& adjacency);

    Graph& graph;
    std::queue<char> nodesQueue;
    std::unique_ptr<std::vector<char>> sequence;
};

#endif

