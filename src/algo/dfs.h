
#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include <memory>
#include <vector>

#include "../graph/graph.h"


class DFS
{
public:

    explicit DFS(Graph&);
    DFS(const DFS&) = delete;
    DFS(DFS&&) = delete;
    DFS& operator=(const DFS&) = delete;
    DFS& operator=(DFS&&) = delete;

    std::unique_ptr<std::vector<char>> traverseGraph(char key);

private:

    void processNode(char key);

    Graph& graph;
    std::unique_ptr<std::vector<char>> sequence;
};

#endif

