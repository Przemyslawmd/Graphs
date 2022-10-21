
#include "graphList.h"
#include <algorithm>
#include <iostream>

GraphList::GraphList(const std::vector<std::vector<char>>& adjacency)
{
    adjacencyList = adjacency;
    
    for (auto vec : adjacency) {
        nodes.push_back(std::make_unique<Node>(vec[0]));
    }
}


std::vector<std::vector<char>>& GraphList::getAdjacencyList()
{
    return adjacencyList;
}


std::map<char, std::list<std::tuple<char, int>>>& GraphList::getAdjacency()
{
    return adjacency;
}


 void GraphList::addNodes(std::vector<char>& nodeKeys)
 {
        for (auto vec : nodeKeys) {
        nodes.push_back(std::make_unique<Node>(vec));
    }
 }


void GraphList::addEdge(char srcKey, char dstKey)
{
    if (std::find_if(nodes.begin(), nodes.end(), [srcKey](const auto& node) { return node.get()->getKey() == srcKey; } ) == nodes.end()) {
        return;    
    }
    if (std::find_if(nodes.begin(), nodes.end(), [dstKey](const auto& node) { return node.get()->getKey() == dstKey; } ) == nodes.end()) {
        return;    
    }
    
    auto itMap = adjacency.find(srcKey);

    if (itMap != adjacency.end()) {
        auto& itList = itMap->second;
        if (std::find_if(itList.begin(), itList.end(), [dstKey](const auto& tup) { return std::get<0>(tup) == dstKey; }) != itList.end()) {
            return;
        }
        itList.push_back(std::make_tuple(dstKey, 1));
        return;  
    }
    adjacency.insert( { srcKey, { std::make_tuple(dstKey, 1) } } );
}

