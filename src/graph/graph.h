
#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <list>
#include <map>
#include <memory>
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

    void removeNode(char);

    void addEdge(char src, char dst);
    void addEdges(char src, const std::vector<char>& dstKeys);
    void addEdgeWeighted(char src, char dstKeys, size_t weight);
    void addEdgesWeighted(char src, const std::vector<std::tuple<char, size_t>>& edges);

    void removeEdge(char srcKey, char dst);

    bool isNodeVisited(char key);
    void setNodeAsVisited(char key);
    void setAllVisitedFlags(bool isVisited);

    void resetColors();
    bool isNodeColored(char key);
    void setNodeColor(char key, uint16_t color);

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

