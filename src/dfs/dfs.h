
#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include "../graph/node.h"
#include "../graph/graph.h"

#include <memory>
#include <queue>
#include <vector>


class DFS
{
public:

    DFS(Graph&);
    DFS(const DFS&) = delete;
    DFS& operator=(DFS&) = delete;

    void traverseGraph();

private:

    void processNode(char key);

    std::vector<std::vector<char>>& adjacency;
    std::vector<std::unique_ptr<Node>>& nodes;
};

#endif

