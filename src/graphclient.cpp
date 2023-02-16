
#include "graphclient.h"

#include <iostream>


GraphClient::GraphClient(GraphMode mode) 
{
    if (mode == GraphMode::List) {
        graph = std::make_unique<GraphList>();
    } 
    else {
        graph = nullptr;
    }
}


void GraphClient::addNode(char key)
{
    graph->addNode(key);
}


void GraphClient::addNodes(const std::vector<char>& keys)
{
    graph->addNodes(keys);
}


void GraphClient::addEdges(char srcKey, const std::vector<char>& dstKeys)
{
    graph->addEdges(srcKey, dstKeys);
}


void GraphClient::addEdgesWithWeight(char srcKey, const std::vector<std::tuple<char, int>>& edges)
{
    graph->addEdgesWithWeight(srcKey, edges);
}

