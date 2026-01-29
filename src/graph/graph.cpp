
#include "graph.h"

#include <algorithm>

#include "logs/logCollector.h"


Graph::Graph(bool isDirected): directed{ isDirected } {}


void Graph::addNode(char key)
{
    if (nodes.size() == MAX_NODES_NUMBER) {
        LogCollector::putError(Error::MAX_NODES);
        return;
    }
    if (isNodeExist(key) == false) {
        nodes.emplace_back(key);
    }
}


void Graph::addNodes(const std::vector<char>& keys)
{
    if (nodes.size() == MAX_NODES_NUMBER) {
        LogCollector::putError(Error::MAX_NODES);
        return;
    }
    for (const auto key : keys) {
        addNode(key);
    }
}


void Graph::removeNode(char key)
{
    if (isNodeExist(key) == false) {
        LogCollector::putError(Error::NO_NODE);
        return;
    }
    std::erase_if(nodes, [key](const auto& node) { return node.getKey() == key; });

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
        createEdge(src, std::get<char>(edge), std::get<size_t>(edge));
    }
}


void Graph::removeEdge(char src, char dst)
{
    deleteEdge(src, dst);
    if (!directed) {
        deleteEdge(dst, src);
    }
}


IsProperty Graph::isNodeVisited(char key)
{
    auto it = findNode(key);
    if (it == nodes.end()) {
        LogCollector::putError(Error::NO_NODE);
        return IsProperty::UNKNOWN;
    }
    return it->visited ? IsProperty::YES : IsProperty::NO;
}


void Graph::setNodeAsVisited(char key)
{
    auto it = findNode(key);
    if (it == nodes.end()) {
        return;
    }
    it->visited = true;
}


void Graph::resetVisitFlags()
{
    for (auto& node : nodes) {
        node.visited = false;
    }
}


void Graph::resetColors()
{
    for (auto& node : nodes) {
        node.color = 0;
    }
}


uint8_t Graph::getNodeColor(char key)
{
    auto it = findNode(key);
    if (it == nodes.end()) {
        LogCollector::putError(Error::NO_NODE);
        return 0;
    }
    return it->color;
}


void Graph::setNodeColor(char key, uint8_t color)
{
    auto it = findNode(key);
    if (it == nodes.end()) {
        LogCollector::putError(Error::NO_NODE);
        return;
    }
    it->color = color;
}


size_t Graph::getSize()
{
    return nodes.size();
}


bool Graph::isEmpty()
{
    return nodes.empty();
}


bool Graph::isDirected()
{
    return directed;
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
    if (!directed) {
        updateAdjacency(dst, src, weight);
    }
}


void Graph::deleteEdge(char src, char dst)
{
    if (adjacency.contains(src) == false) {
        LogCollector::putError(Error::NO_CONNECTION);
        return;
    }

    auto& edges = adjacency.at(src);
    auto it = std::find_if(edges.begin(), edges.end(), [dst](const auto& edge) { return edge.dst == dst; });
    if (it == edges.end()) {
        LogCollector::putError(Error::NO_CONNECTION);
        return;
    }
    edges.erase(it);

    if (adjacency.at(src).empty()) {
        adjacency.erase(src);
    }
}


void Graph::updateAdjacency(char src, char dst, size_t weight)
{
    if (adjacency.contains(src) == false) {
        adjacency.insert({ src, {{ src, dst, weight }}});
        return;
    }

    auto& adjacentNodes = adjacency.at(src);
    if (std::none_of(adjacentNodes.begin(), adjacentNodes.end(), [dst](const auto& edge) { return edge.dst == dst; })) {
        adjacentNodes.emplace_back( src, dst, weight );
    }
}


bool Graph::isNodeExist(char key)
{
    return std::any_of(nodes.begin(), nodes.end(), [key](const auto& node) { return node.getKey() == key; });
}


std::vector<Node>::iterator Graph::findNode(const char key)
{
    auto it = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.getKey() == key; });
    if (it == nodes.end()) {
        LogCollector::putError(Error::NO_NODE);
    }
    return it;
}

