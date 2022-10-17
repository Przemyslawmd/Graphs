
#include "graphMatrix.h"



GraphMatrix::GraphMatrix(const std::vector<std::vector<int>>& adjacency)
{
    adjacencyMatrix = adjacency;
    
    for (auto vec : adjacency) {
        nodes.push_back(std::make_unique<Node>(vec[0]));
    }
}


std::vector<std::vector<int>>& GraphMatrix::getAdjacencyMatrix()
{
    return adjacencyMatrix;
}

