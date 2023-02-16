
#include "graphList.h"
#include <algorithm>
#include <iostream>


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

