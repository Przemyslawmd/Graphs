
#include "bfs.h"


BFS::BFS(Graph& graph) : graph(graph)
{
    sequence = std::make_unique<std::vector<char>>();
}


std::unique_ptr<std::vector<char>> BFS::traverseGraph(char key)
{
    graph.setAllVisitedFlags(false);
    const auto& adjacency = graph.getAdjacency();
    nodesQueue.push(key);

    while (nodesQueue.empty() == false) {
        processQueue(adjacency);
        nodesQueue.pop();
    }
    return std::move(sequence);
}


void BFS::processQueue(const std::map<char, std::list<Edge>>& adjacency)
{
    char key = nodesQueue.front();
    graph.setNodeAsVisited(key);
    sequence->push_back(key);

    for (const auto& edge : adjacency.at(key)) {
        if (graph.isNodeVisited(edge.dst) == false) {
            nodesQueue.emplace(edge.dst);
            graph.setNodeAsVisited(edge.dst);
        }
    }
}

