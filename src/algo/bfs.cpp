
#include "bfs.h"

#include <iterator>


BFS::BFS(Graph& graph) : graph(graph) {}


void BFS::traverseGraph()
{
    graph.setAllNodesAsNotVisited();
    const auto& adjacency = graph.getAdjacency();
    nodesQueue.push(adjacency.begin()->first);
    
    while (!nodesQueue.empty()) {
        processQueue(adjacency);
        nodesQueue.pop();
    }
}


void BFS::processQueue(const std::map<char, std::list<Edge>>& adjacency)
{
    char key = nodesQueue.front();
    graph.setNodeAsVisited(key);

    for (auto& edge : adjacency.at(key)) {
        if (graph.isNodeVisited(edge.dst) == false) {
            nodesQueue.push(edge.dst);
            graph.setNodeAsVisited(edge.dst);
        }
    }
}

