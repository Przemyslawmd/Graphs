
#include "dfs.h"

#include <iterator>


DFS::DFS(GraphList& graph) : graph(graph) {}


void DFS::traverseGraph()
{
    const auto& adjacency = graph.getAdjacency();
    char initialKey = adjacency.begin()->first;        
    processNode(initialKey);   
}


void DFS::processNode(char key)
{
    graph.setNodeVisit(key, true);
    const auto& adjacentNodes = graph.getAdjacency().at(key);

    for (auto itNode = adjacentNodes.begin(); itNode != adjacentNodes.end(); itNode++) {
        if (graph.isNodeVisited(itNode->dstKey) == false) {
            processNode(itNode->dstKey);
        }
    }
}

