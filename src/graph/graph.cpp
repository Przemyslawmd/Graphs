
#include "graph.h"

#include <algorithm>

#include "logs/logCollector.h"


Graph::Graph(bool isDirected): isDirected(isDirected) {}


void Graph::addNode(char key)
{
    if (isNodeExist(key) == false) {
        nodes.emplace_back(key);
    }
}


void Graph::addNodes(const std::vector<char>& keys)
{
    for (const auto key : keys) {
        addNode(key);
    }
}


void Graph::removeNode(char key)
{
    if (isNodeExist(key) == false) {
        LogCollector::putError(Error::NODE_NOT_EXISTS);
        return;
    }
    std::erase_if(nodes, [key](const auto& node) { return node.key == key; });

    if (adjacency.contains(key)) {
        adjacency.erase(key);
    }

    for (auto& [_, value] : adjacency) {
        value.remove_if([key](const auto& edge) { return edge.dst == key; });
    }
}


const std::vector<Node>& Graph::getNodes()
{
    return nodes;
}


const std::map<char, std::list<Edge>>& Graph::getAdjacency()
{
    return adjacency;
}


void Graph::addEdge(char src, char dst)
{
    createEdge(src, dst, 1);
}


void Graph::addEdges(char src, const std::vector<char>& dstKeys)
{
    for (char dst : dstKeys) {
        createEdge(src, dst, 1);
    }
}


void Graph::addEdgeWeighted(char src, char dst, size_t weight)
{
    createEdge(src, dst, weight);
}


void Graph::addEdgesWeighted(char src, const std::vector<std::tuple<char, size_t>>& edges)
{
    for (const auto& edge : edges) {
        createEdge(src, std::get<0>(edge), std::get<1>(edge));
    }
}


bool Graph::isNodeVisited(char key)
{
    const auto it = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.key == key; });
    if (it == nodes.end()) {
        LogCollector::putError(Error::NODE_NOT_EXISTS);
        return false;
    }
    return it->isVisited();
}


void Graph::setNodeAsVisited(char key)
{
    const auto it = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.key == key; });
    if (it == nodes.end()) {
        LogCollector::putError(Error::NODE_NOT_EXISTS);
        return;
    }
    it->setVisited(true);
}


void Graph::setAllVisitedFlags(bool isVisited)
{
    for (auto& node : nodes) {
        node.setVisited(isVisited);
    }
}

/************************************** PRIVATE ***********************************************/
/**********************************************************************************************/


void Graph::createEdge(char src, char dst, size_t weight)
{
    if (isNodeExist(src) == false) {
        nodes.emplace_back(src);
    }
    if (isNodeExist(dst) == false) {
        nodes.emplace_back(dst);
    }

    updateAdjacency(src, dst, weight);
    if (isDirected == false) {
        updateAdjacency(dst, src, weight);
    } 
}


void Graph::updateAdjacency(char src, char dst, size_t weight)
{
    if (adjacency.count(src) != 1) {
        adjacency.insert({ src, {{ src, dst, weight }}});
        return;
    }

    auto& adjacentNodes = adjacency.at(src);
    auto it = std::find_if(adjacentNodes.begin(), adjacentNodes.end(), [dst](const auto& edge) { return edge.dst == dst; });
    if (it == adjacentNodes.end()) {
        adjacentNodes.emplace_back( src, dst, weight );
    }
}


bool Graph::isNodeExist(char key)
{
    return std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.key == key; }) != nodes.end();
}

