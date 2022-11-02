
#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include "../graph/edge.h"
#include "../graph/node.h"
#include "../graph/graphList.h"

#include <memory>
#include <queue>
#include <vector>


class DFS
{
public:

    DFS(GraphList&);
    DFS(const DFS&) = delete;
    DFS& operator=(DFS&) = delete;

    void traverseGraph();

private:

    void processNode(char key);

    std::map<char, std::list<Edge>>& adjacency;
    const std::vector<std::unique_ptr<Node>>& nodes;
};

#endif

