
#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <list>
#include <map>
#include <memory>
#include <vector>

#include "edge.h"
#include "node.h"


enum class IsProperty 
{
    NO, 
    YES,
    UNKNOWN
};


class Graph
{
public:

    Graph(bool isDirected = true);
    Graph(const Graph&) = delete;
    Graph& operator=(Graph&) = delete;

    void addNode(char key);
    void addNodes(const std::vector<char>& keys);
    const std::vector<Node>& getNodes();

    void removeNode(char);

    void addEdge(char src, char dst);
    void addEdges(char src, const std::vector<char>& dstKeys);
    void addEdgeWeighted(char src, char dstKeys, size_t weight);
    void addEdgesWeighted(char src, const std::vector<std::tuple<char, size_t>>& edges);

    void removeEdge(char srcKey, char dst);

    IsProperty isNodeVisited(char key);
    void setNodeAsVisited(char key);
    void setAllVisitedFlags(bool isVisited);

    void resetColors();
    void setNodeColor(char key, uint16_t color);
    uint16_t getNodeColor(char key);

    size_t getSize();

    const std::map<char, std::list<Edge>>& getAdjacency();

private:

    void createEdge(char src, char dst, size_t  weight);
    void deleteEdge(char src, char dst);
    void updateAdjacency(char src, char dst, size_t weight);

    bool isNodeExist(char key);
    std::vector<Node>::iterator findNode(const char key);

    const bool isDirected;

    std::vector<Node> nodes;
    std::map<char, std::list<Edge>> adjacency;
};

#endif

