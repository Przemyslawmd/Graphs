
#include "dfs.h"

#include <iterator>


DFS::DFS(GraphList& graph) : graph(graph) {}


void DFS::traverseGraph()
{
    const auto& adjacency = graph.getAdjacency();
    char initialKey = adjacency.begin()->first;        
    processNode(initialKey);   
}


void DFS::processNode(char key)
{
    graph.setNodeVisit(key, true);
    auto& adjacentNodesList = graph.getAdjacency()[key];

    for (auto it = adjacentNodesList.begin(); it != adjacentNodesList.end(); it++) {
        if (graph.isNodeVisited(it->dstKey) == false) {
            processNode(it->dstKey);
        }
    }
}

