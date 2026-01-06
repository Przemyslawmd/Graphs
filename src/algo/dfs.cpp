
#include "dfs.h"


DFS::DFS(Graph& graph) : graph(graph) {}


std::unique_ptr<std::vector<char>> DFS::traverseGraph(const char key)
{
    nodesSequence = std::make_unique<std::vector<char>>();
    graph.setAllVisitedFlags(false);
    processNode(key);
    return std::move(nodesSequence);
}


void DFS::processNode(const char key)
{
    graph.setNodeAsVisited(key);
    nodesSequence->push_back(key);

    const auto& adjacency = graph.getAdjacency();
    if (adjacency.contains(key) == false) {
        return;
    }

    const auto& adjacentNodes = adjacency.at(key);
    for (const auto& edge : adjacentNodes) {
        if (graph.isNodeVisited(edge.dst) == false) {
            processNode(edge.dst);
        }
    }
}

