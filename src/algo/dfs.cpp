
#include "dfs.h"

#include <iterator>


DFS::DFS(GraphList& graph) : nodes(graph.getNodes()), adjacency(graph.getAdjacency()) {}


void DFS::traverseGraph()
{
    char initialKey = adjacency.begin()->first;        
    processNode(initialKey);   
}


void DFS::processNode(char key)
{
    auto itNode = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node->getKey() == key; });
    (*itNode)->setAsVisited();

    auto& itNeighboursList = adjacency[key];
    auto it = itNeighboursList.begin();
     
    while (it != itNeighboursList.end()) {
        auto itNeighbourNode = std::find_if(nodes.begin(), nodes.end(), [it](const auto& node) { return node->getKey() == std::get<0>(*it); });
        if ((*itNeighbourNode).get()->isVisited() == false) {
            processNode(std::get<0>(*it));
        }
        it++;
    }
}

