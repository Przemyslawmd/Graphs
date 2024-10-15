
#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <list>
#include <map>
#include <memory>
#include <tuple>
#include <vector>

#include "edge.h"
#include "node.h"


class Graph
{
public:
    
    Graph(bool isDirected = true, bool isWeighted = true);
    Graph(const Graph&) = delete;
    Graph& operator=(Graph&) = delete;
        
    void addNode(char key);
    void addNodes(const std::vector<char>& keys);
    const std::vector<Node>& getNodes();
    
    void addEdges(char srcKey, const std::vector<char>& dstKeys);
    void addEdgesWeighted(char srcKey, const std::vector<std::tuple<char, int>>& edges);

    bool isNodeVisited(char key);
    void setNodeAsVisited(char key);
    void setAllNodesAsNotVisited();

    const std::map<char, std::list<Edge>>& getAdjacency();

private:

    void addEdge(char srcKey, char dstKey, int weight);
    void updateAdjacency(char srcKey, char dstKey, int weight);

    bool isNodeExist(char key);

    const bool isWeighted;
    const bool isDirected;

    std::vector<Node> nodes;
    std::map<char, std::list<Edge>> adjacency;
};

#endif

