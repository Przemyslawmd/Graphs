
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

    Graph(bool isDirected = true);
    Graph(const Graph&) = delete;
    Graph& operator=(Graph&) = delete;

    void addNode(char key);
    void addNodes(const std::vector<char>& keys);
    const std::vector<Node>& getNodes();

    void addEdge(char srcKey, char dst);
    void addEdges(char srcKey, const std::vector<char>& dstKeys);
    void addEdgeWeighted(char srcKey, char dstKeys, size_t weight);
    void addEdgesWeighted(char srcKey, const std::vector<std::tuple<char, size_t>>& edges);

    bool isNodeVisited(char key);
    void setNodeAsVisited(char key);
    void setAllVisitedFlags(bool isVisited);

    const std::map<char, std::list<Edge>>& getAdjacency();

private:

    void createEdge(char srcKey, char dstKey, size_t  weight);
    void updateAdjacency(char srcKey, char dstKey, size_t weight);

    bool isNodeExist(char key);

    const bool isDirected;

    std::vector<Node> nodes;
    std::map<char, std::list<Edge>> adjacency;
};

#endif

