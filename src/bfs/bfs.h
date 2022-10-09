
#ifndef GRAPHS_BFS_H
#define GRAPHS_BFS_H

#include "../graph/node.h"
#include "../graph/graph.h"

#include <memory>
#include <queue>
#include <vector>


class BFS
{
public:

    void traverseGraph(Graph& graph);

private:

    void processQueue(std::vector<std::vector<char>>& adjacencyList, std::vector<std::unique_ptr<Node>>& nodes);
    
    std::queue<char> nodesQueue;
};

#endif

