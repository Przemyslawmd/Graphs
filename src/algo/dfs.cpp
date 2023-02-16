
#include "dfs.h"

#include <iterator>


DFS::DFS(Graph& graph) : graph(graph) {}


void DFS::traverseGraph()
{
    const auto& adjacency = graph.getAdjacency();
    char initialKey = adjacency.begin()->first;        
    processNode(initialKey);   
}


void DFS::processNode(char key)
{
    graph.setNodeVisit(key, true);

    const auto& adjacentNodes = graph.getAdjacency().at(key);
    for (auto& edge : adjacentNodes) {
        if (graph.isNodeVisited(edge.dst) == false) {
            processNode(edge.dst);
        }
    }
}

