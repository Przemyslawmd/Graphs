
#ifndef GRAPHS_GRAPHLIST_H
#define GRAPHS_GRAPHLIST_H

#include "graph.h"
#include "node.h"

#include <memory>
#include <vector>


class GraphList : public Graph
{
public:
    
    virtual ~GraphList() {};
    GraphList(const std::vector<std::vector<char>>& adjacency);
    GraphList(const GraphList&) = delete;
    GraphList& operator=(GraphList&) = delete;

    //std::vector<std::unique_ptr<Node>>& getNodes();
    std::vector<std::vector<char>>& getAdjacencyList();
    //std::vector<std::vector<int>>& getAdjacencyMatrix();

private:

    //std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::vector<char>> adjacencyList;
    //std::vector<std::vector<int>> adjacencyMatrix;
};

#endif

