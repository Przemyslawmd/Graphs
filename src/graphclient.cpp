
#include "graphclient.h"


GraphClient::GraphClient() 
{
    graph = std::make_unique<GraphList>();
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

