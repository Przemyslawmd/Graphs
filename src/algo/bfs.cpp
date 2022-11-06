
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

    auto& neighbours = adjacency.at(key);
    for (auto it = neighbours.begin(); it != neighbours.end(); it++) {
        if (graph.isNodeVisited(it->dstKey) == false) {
            nodesQueue.push(it->dstKey);
            graph.setNodeVisit(it->dstKey, true);
        }
    }    
    
    nodesQueue.pop();  
}

