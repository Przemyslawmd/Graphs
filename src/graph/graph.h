
#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include "node.h"

#include <memory>
#include <vector>

class Graph
{
public:
    
    Graph(std::vector<std::vector<char>> adjacency); 

    std::vector<std::unique_ptr<Node>>& getNodes();
    std::vector<std::vector<char>>& getAdjacencyList();

private:

    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::vector<char>> adjacencyList;
};

#endif

