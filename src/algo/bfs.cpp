
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

    for (auto& edge : adjacency.at(key)) {
        if (graph.isNodeVisited(edge.dstKey) == false) {
            nodesQueue.push(edge.dstKey);
            graph.setNodeVisit(edge.dstKey, true);
        }
    }

    nodesQueue.pop();  
}

