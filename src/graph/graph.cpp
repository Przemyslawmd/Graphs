
#include "graph.h"


Graph::Graph(const std::vector<std::vector<char>>& adjacency)
{
    adjacencyList = adjacency;
    
    for (auto vec : adjacency) {
        nodes.push_back(std::make_unique<Node>(vec[0]));
    }
}


std::vector<std::unique_ptr<Node>>& Graph::getNodes()
{
    return nodes;
}


std::vector<std::vector<char>>& Graph::getAdjacencyList()
{
    return adjacencyList;
}

