
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
    bool isNodeExist(char key);
    void resetNodes();

    const std::vector<std::unique_ptr<Node>>& getNodes();

protected:

    std::vector<std::unique_ptr<Node>> nodes;
};

#endif

