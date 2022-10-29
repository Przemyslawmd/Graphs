
#include "graphList.h"
#include <algorithm>
#include <iostream>


std::map<char, std::list<std::tuple<char, int>>>& GraphList::getAdjacency()
{
    return adjacency;
}


void GraphList::addNodes(const std::vector<char>& keysVec)
{
    for (auto key : keysVec) {
        nodes.push_back(std::make_unique<Node>(key));
    }
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
    if (isNodeNotExist(srcKey)) {
        return;    
    }
    if (isNodeNotExist(dstKey)) {
        return;
    }
    
    auto srcKeyAdjacency = adjacency.find(srcKey);
    if (srcKeyAdjacency == adjacency.end()) {
        adjacency.insert( { srcKey, { std::make_tuple(dstKey, weight) }});
        return;
    }
    
    auto& adjacencyList = srcKeyAdjacency->second;
    if (std::find_if(adjacencyList.begin(), adjacencyList.end(), [dstKey](const auto& tuple) { return std::get<0>(tuple) == dstKey; }) == adjacencyList.end()) {
        adjacencyList.push_back(std::make_tuple(dstKey, weight));
    }
}

