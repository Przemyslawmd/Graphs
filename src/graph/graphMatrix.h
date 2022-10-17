
#ifndef GRAPHS_GRAPHMATRIX_H
#define GRAPHS_GRAPHMATRIX_H

#include "graph.h"
#include "node.h"

#include <memory>
#include <vector>


class GraphMatrix : public Graph
{
public:
    
    virtual ~GraphMatrix() {};
    GraphMatrix(const std::vector<std::vector<int>>& adjacency);
    GraphMatrix(const GraphMatrix&) = delete;
    GraphMatrix& operator=(GraphMatrix&) = delete;

    std::vector<std::vector<int>>& getAdjacencyMatrix();

private:

    std::vector<std::vector<int>> adjacencyMatrix;
};

#endif

