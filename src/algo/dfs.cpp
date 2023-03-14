
#include "dfs.h"

#include <iterator>


DFS::DFS(Graph& graph) : graph(graph) {}


void DFS::traverseGraph()
{
    graph.setAllNodesAsNotVisited();
    const auto& adjacency = graph.getAdjacency();
    char initialKey = adjacency.begin()->first;        
    processNode(initialKey);   
}


void DFS::processNode(char key)
{
    graph.setNodeAsVisited(key);

    const auto& adjacentNodes = graph.getAdjacency().at(key);
    for (auto& edge : adjacentNodes) {
        if (graph.isNodeVisited(edge.dst) == false) {
            processNode(edge.dst);
        }
    }
}

