
#include "graphList.h"
#include <algorithm>
#include <iostream>


const std::vector<std::unique_ptr<Node>>& GraphList::getNodes()
{
    return nodes;
}


void GraphList::addNode(char key)
{
    if (isNodeExist(key) == false) {
        nodes.push_back(std::make_unique<Node>(key));
    }
}


void GraphList::addNodes(const std::vector<char>& keys)
{
    for (auto key : keys) {
        nodes.push_back(std::make_unique<Node>(key));
    }
}


bool GraphList::isNodeExist(char key)
{
    return std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.get()->getKey() == key; }) != nodes.end();
}


const std::map<char, std::list<Edge>>& GraphList::getAdjacency()
{
    return adjacency;
}


void GraphList::addEdges(char srcKey, const std::vector<char>& dstKeysVec)
{
    for (char dstKey : dstKeysVec) {
        addEdge(srcKey, dstKey, 1);
    }
}


void GraphList::addEdgesWithWeight(char srcKey, const std::vector<std::tuple<char, int>>& edgesVec)
{
    for (const auto& edge : edgesVec) {
        addEdge(srcKey, std::get<0>(edge), std::get<1>(edge));
    }
}


void GraphList::addEdge(char srcKey, char dstKey, int weight)
{
    if (isNodeExist(srcKey) == false) {
        return;    
    }
    if (isNodeExist(dstKey) == false) {
        return;
    }
    
    if (adjacency.count(srcKey) != 1) {
        adjacency.insert({ srcKey, { Edge{ srcKey, dstKey, weight }}});
        return;
    }
    
    auto& adjacentNodes = adjacency.at(srcKey);
    auto it = std::find_if(adjacentNodes.begin(), adjacentNodes.end(), [dstKey](const auto& edge) { return edge.dst == dstKey; });
    if (it == adjacentNodes.end()) {
        adjacentNodes.push_back(Edge{ srcKey, dstKey, weight });
    }
}


bool GraphList::isNodeVisited(char key)
{
    auto node = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.get()->getKey() == key; });
    return node->get()->isVisited();
}


void GraphList::setNodeVisit(char key, bool isVisited)
{
    auto node = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.get()->getKey() == key; });
    node->get()->setVisited(isVisited);
}


void GraphList::resetNodes()
{
    for (auto& node : nodes) {
        node->setVisited(false);
    }
}