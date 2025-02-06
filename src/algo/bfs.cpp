
#include "bfs.h"

#include <iterator>


BFS::BFS(Graph& graph) : graph(graph) {}


void BFS::traverseGraph()
{
    graph.setAllVisitedFlags(false);
    const auto& adjacency = graph.getAdjacency();
    nodesQueue.push(adjacency.begin()->first);

    while (nodesQueue.empty() == false) {
        processQueue(adjacency);
        nodesQueue.pop();
    }
}


void BFS::processQueue(const std::map<char, std::list<Edge>>& adjacency)
{
    char key = nodesQueue.front();
    graph.setNodeAsVisited(key);

    for (const auto& edge : adjacency.at(key)) {
        if (graph.isNodeVisited(edge.dst) == false) {
            nodesQueue.emplace(edge.dst);
            graph.setNodeAsVisited(edge.dst);
        }
    }
}

