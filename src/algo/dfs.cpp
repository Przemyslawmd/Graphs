
#include "dfs.h"


DFS::DFS(Graph& graph) : graph(graph) 
{
    sequence = std::make_unique<std::vector<char>>();
}


std::unique_ptr<std::vector<char>> DFS::traverseGraph(char key)
{
    graph.setAllVisitedFlags(false);
    processNode(key);
    return std::move(sequence);
}


void DFS::processNode(char key)
{
    graph.setNodeAsVisited(key);
    sequence->push_back(key);

    const auto& adjacentNodes = graph.getAdjacency().at(key);
    for (const auto& edge : adjacentNodes) {
        if (graph.isNodeVisited(edge.dst) == false) {
            processNode(edge.dst);
        }
    }
}

