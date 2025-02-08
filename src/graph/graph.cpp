
#include "graph.h"

#include <algorithm>
#include <iostream>


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


bool Graph::isNodeExist(char key)
{
    return std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.key == key; }) != nodes.end();
}


const std::vector<Node>& Graph::getNodes()
{
    return nodes;
}


const std::map<char, std::list<Edge>>& Graph::getAdjacency()
{
    return adjacency;
}


void Graph::addEdge(char srcKey, char dstKey)
{
    createEdge(srcKey, dstKey, 1);
}


void Graph::addEdges(char srcKey, const std::vector<char>& dstKeys)
{
    for (char dstKey : dstKeys) {
        createEdge(srcKey, dstKey, 1);
    }
}


void Graph::addEdgeWeighted(char srcKey, char dstKey, size_t weight)
{
    createEdge(srcKey, dstKey, weight);
}


void Graph::addEdgesWeighted(char srcKey, const std::vector<std::tuple<char, size_t>>& edges)
{
    for (const auto& edge : edges) {
        createEdge(srcKey, std::get<0>(edge), std::get<1>(edge));
    }
}


void Graph::createEdge(char srcKey, char dstKey, size_t weight)
{
    if (isNodeExist(srcKey) == false) {
        nodes.emplace_back(srcKey);
    }
    if (isNodeExist(dstKey) == false) {
        nodes.emplace_back(dstKey);
    }

    updateAdjacency(srcKey, dstKey, weight);
    if (isDirected == false) {
        updateAdjacency(dstKey, srcKey, weight);
    } 
}


void Graph::updateAdjacency(char srcKey, char dstKey, size_t weight)
{
    if (adjacency.count(srcKey) != 1) {
        adjacency.insert({ srcKey, {{ srcKey, dstKey, weight }}});
        return;
    }

    auto& adjacentNodes = adjacency.at(srcKey);
    auto it = std::find_if(adjacentNodes.begin(), adjacentNodes.end(), [dstKey](const auto& edge) { return edge.dst == dstKey; });
    if (it == adjacentNodes.end()) {
        adjacentNodes.emplace_back( srcKey, dstKey, weight );
    }
}


bool Graph::isNodeVisited(char key)
{
    const auto it = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.key == key; });
    return (*it).isVisited();
}


void Graph::setNodeAsVisited(char key)
{
    const auto it = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.key == key; });
    (*it).setVisited(true);
}


void Graph::setAllVisitedFlags(bool isVisited)
{
    for (auto& node : nodes) {
        node.setVisited(isVisited);
    }
}

