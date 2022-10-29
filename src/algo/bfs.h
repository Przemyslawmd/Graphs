
#ifndef GRAPHS_BFS_H
#define GRAPHS_BFS_H

#include "../graph/node.h"
#include "../graph/graphList.h"
#include "../graph/graphMatrix.h"

#include <memory>
#include <queue>
#include <vector>


class BFS
{
public:

    BFS() = default;
    BFS(const BFS&) = delete;
    BFS& operator=(BFS&) = delete;

    void traverseGraph(GraphList& graph);

private:

    void processQueue(std::map<char, std::list<std::tuple<char, int>>>& adjacency , std::vector<std::unique_ptr<Node>>& nodes);

    std::queue<char> nodesQueue;
};

#endif

