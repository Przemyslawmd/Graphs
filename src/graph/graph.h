
#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <list>
#include <map>
#include <memory>
#include <vector>

#include "edge.h"
#include "node.h"

constexpr size_t MAX_NODES_NUMBER = 255;

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

    void removeEdge(char src, char dst);

    IsProperty isNodeVisited(char key);
    void setNodeAsVisited(char key);
    void resetVisitFlags();

    void resetColors();
    void setNodeColor(char key, uint8_t color);
    uint8_t getNodeColor(char key);

    size_t getSize();
    bool isEmpty();
    bool isDirected();

    const std::map<char, std::list<Edge>>& getAdjacency();

private:

    void createEdge(char src, char dst, size_t weight);
    void deleteEdge(char src, char dst);
    void updateAdjacency(char src, char dst, size_t weight);

    bool isNodeExist(char key);
    std::vector<Node>::iterator findNode(const char key);

    const bool directed;

    std::vector<Node> nodes;
    std::map<char, std::list<Edge>> adjacency;
};

#endif

