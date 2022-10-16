
#include "graph.h"


Graph::Graph(const std::vector<std::vector<char>>& adjacency)
{
    adjacencyList.reserve(adjacency.size() * adjacency.size());
    adjacencyList.insert(adjacencyList.begin(), adjacency.begin(), adjacency.end());   
    
    int i = 0;
    for (auto vec : adjacency) {
        adjacencyList.at(i).insert(adjacencyList.at(i).begin(), vec.begin(), vec.end());
        nodes.push_back(std::make_unique<Node>(vec.at(0)));
        i++;
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

