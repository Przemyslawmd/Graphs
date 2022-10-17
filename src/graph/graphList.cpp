
#include "graphList.h"


GraphList::GraphList(const std::vector<std::vector<char>>& adjacency)
{
    adjacencyList = adjacency;
    
    for (auto vec : adjacency) {
        nodes.push_back(std::make_unique<Node>(vec[0]));
    }
}


std::vector<std::vector<char>>& GraphList::getAdjacencyList()
{
    return adjacencyList;
}

