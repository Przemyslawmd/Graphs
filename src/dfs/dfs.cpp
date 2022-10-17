
#include "dfs.h"

#include <iterator>


DFS::DFS(GraphList& graph) : adjacency(graph.getAdjacencyList()), nodes(graph.getNodes()) {}


void DFS::traverseGraph()
{
    char initialKey = adjacency.at(0).at(0);        
    processNode(initialKey);   
}


void DFS::processNode(char key)
{
    auto itNode = std::find_if(nodes.begin(), nodes.end(), [&](const auto& node) { return node->getKey() == key; });
    (*itNode)->setAsVisited();

    auto itNeighbours = std::find_if(adjacency.begin(), adjacency.end(), [&](const auto& vec) { return vec.at(0) == key; });
    std::vector<char>::iterator it = itNeighbours->begin();
    std::advance(it, 1);
     
    while (it != itNeighbours->end()) {
        auto itNode = std::find_if(nodes.begin(), nodes.end(), [&](const auto& node) { return node->getKey() == *it; });
        if ((*itNode).get()->isVisited() == false) {
            processNode(*it);
        }
        it++;
    }
}

