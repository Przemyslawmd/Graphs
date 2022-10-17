
#include "dfs.h"

#include <iterator>


DFS::DFS(GraphList& graph) : adjacency(graph.getAdjacencyList()), nodes(graph.getNodes()) {}


void DFS::traverseGraph()
{
    char initialKey = adjacency[0][0];        
    processNode(initialKey);   
}


void DFS::processNode(char key)
{
    auto itNode = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node->getKey() == key; });
    (*itNode)->setAsVisited();

    auto itNeighboursList = std::find_if(adjacency.begin(), adjacency.end(), [key](const auto& vec) { return vec[0] == key; });
    std::vector<char>::iterator it = itNeighboursList->begin();
    std::advance(it, 1);
     
    while (it != itNeighboursList->end()) {
        auto itNeighbourNode = std::find_if(nodes.begin(), nodes.end(), [it](const auto& node) { return node->getKey() == *it; });
        if ((*itNeighbourNode).get()->isVisited() == false) {
            processNode(*it);
        }
        it++;
    }
}

