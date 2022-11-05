
#include "bfs.h"

#include <iterator>


BFS::BFS(GraphList& graph) : graph(graph) {}


void BFS::traverseGraph()
{
    auto& adjacency = graph.getAdjacency();
    nodesQueue.push(adjacency.begin()->first);
    
    while (!nodesQueue.empty()) {
        processQueue(adjacency);
    }
}

void BFS::processQueue(std::map<char, std::list<Edge>>& adjacency)
{
    char key = nodesQueue.front();
    graph.setNodeVisit(key, true);

    auto& neighbours = adjacency[key];
    for (auto it = neighbours.begin(); it != neighbours.end(); it++) {
        if (graph.isNodeVisited(it->dstKey) == false) {
            nodesQueue.push(it->dstKey);
            graph.setNodeVisit(it->dstKey, true);
        }
    }    
    
    nodesQueue.pop();  
}

