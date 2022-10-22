
#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include "node.h"

#include <memory>
#include <vector>


class Graph
{
public:
    
    virtual ~Graph() = 0;

    void addNode(char key);
    void virtual addEdge(char key1, char key2) = 0;
    bool isNodeNotExist(char key);
        
    std::vector<std::unique_ptr<Node>>& getNodes();

protected:

    std::vector<std::unique_ptr<Node>> nodes;
};

#endif

