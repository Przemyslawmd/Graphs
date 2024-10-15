
#include "graph.h"

#include <algorithm>
#include <iostream>


Graph::Graph(bool isDirected, bool isWeighted): isDirected(isDirected), isWeighted(isWeighted) {}


void Graph::addNode(char key)
{
    if (isNodeExist(key) == false) {
        nodes.emplace_back(key);
    }
}


void Graph::addNodes(const std::vector<char>& keys)
{
    for (auto key : keys) {
        addNode(key);
    }
}


bool Graph::isNodeExist(char key)
{
    return std::all_of(nodes.begin(), nodes.end(), [key](const auto& node) { return node.key != key; }) == false;
}


const std::vector<Node>& Graph::getNodes()
{
    return nodes;
}


const std::map<char, std::list<Edge>>& Graph::getAdjacency()
{
    return adjacency;
}


void Graph::addEdges(char srcKey, const std::vector<char>& dstKeysVec)
{
    if (isWeighted) {
        std::cout << "Graph is weighted, use addEdgesWeighted function" << std::endl;
        return;
    }
    for (char dstKey : dstKeysVec) {
        addEdge(srcKey, dstKey, 1);
    }
}


void Graph::addEdgesWeighted(char srcKey, const std::vector<std::tuple<char, int>>& edges)
{
    if (isWeighted == false) {
        std::cout << "Graph is not weighted, use addEdges function" << std::endl;
        return;
    }
    for (const auto& edge : edges) {
        addEdge(srcKey, std::get<0>(edge), std::get<1>(edge));
    }
}


void Graph::addEdge(char srcKey, char dstKey, int weight)
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


void Graph::updateAdjacency(char srcKey, char dstKey, int weight)
{
    if (adjacency.count(srcKey) != 1) {
        adjacency.insert({ srcKey, { Edge{ srcKey, dstKey, weight }}});
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


void Graph::setAllNodesAsNotVisited()
{
    for (auto& node : nodes) {
        node.setVisited(false);
    }
}

