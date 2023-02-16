
#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include "node.h"

#include <memory>
#include <vector>


class Graph
{
public:
    
    virtual ~Graph() = 0;

    virtual void addEdges(char srcKey, const std::vector<char>& dstKeys) = 0;
    virtual void addEdgesWithWeight(char srcKey, const std::vector<std::tuple<char, int>>& edges) = 0;

    void addNode(char key);
    void addNodes(const std::vector<char>& keys);
    bool isNodeExist(char key);

    bool isNodeVisited(char key);
    void setNodeVisit(char key, bool isVisited);
    void resetNodes();

    const std::vector<std::unique_ptr<Node>>& getNodes();

protected:

    std::vector<std::unique_ptr<Node>> nodes;
};

#endif

