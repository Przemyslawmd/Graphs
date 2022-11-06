
#include "bfs.h"

#include <iterator>


BFS::BFS(GraphList& graph) : graph(graph) {}


void BFS::traverseGraph()
{
    const auto& adjacency = graph.getAdjacency();
    nodesQueue.push(adjacency.begin()->first);
    
    while (!nodesQueue.empty()) {
        processQueue(adjacency);
    }
}


void BFS::processQueue(const std::map<char, std::list<Edge>>& adjacency)
{
    char key = nodesQueue.front();
    graph.setNodeVisit(key, true);

    const auto& adjacentNodes = adjacency.at(key);
    for (auto itNode = adjacentNodes.begin(); itNode != adjacentNodes.end(); itNode++) {
        if (graph.isNodeVisited(itNode->dstKey) == false) {
            nodesQueue.push(itNode->dstKey);
            graph.setNodeVisit(itNode->dstKey, true);
        }
    }    
    
    nodesQueue.pop();  
}

