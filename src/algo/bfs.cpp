
#include "bfs.h"


BFS::BFS(Graph& graph) : graph(graph) {}


std::unique_ptr<std::vector<char>> BFS::traverseGraph(char key)
{
    nodesSequence = std::make_unique<std::vector<char>>();
    graph.setAllVisitedFlags(false);
    const auto& adjacency = graph.getAdjacency();
    nodesQueue.push(key);

    while (nodesQueue.empty() == false) {
        processQueue(adjacency);
        nodesQueue.pop();
    }
    return std::move(nodesSequence);
}


void BFS::processQueue(const std::map<char, std::list<Edge>>& adjacency)
{
    const char key = nodesQueue.front();
    graph.setNodeAsVisited(key);
    nodesSequence->push_back(key);

    if (adjacency.contains(key) == false) {
        return;
    }

    for (const auto& edge : adjacency.at(key)) {
        if (graph.isNodeVisited(edge.dst) == false) {
            nodesQueue.push(edge.dst);
            graph.setNodeAsVisited(edge.dst);
        }
    }
}

