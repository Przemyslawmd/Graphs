
#include "bfs.h"

#include <iterator>


void BFS::traverseGraph(GraphList& graph)
{
    auto& nodes = graph.getNodes();
    auto& adjacency = graph.getAdjacencyList();
    
    nodesQueue.push(adjacency[0][0]);
    
    while (!nodesQueue.empty()) {
        processQueue(adjacency, nodes);
    }
}


void BFS::processQueue(std::vector<std::vector<char>>& adjacency, std::vector<std::unique_ptr<Node>>& nodes)
{
    char key = nodesQueue.front();
    auto itNode = std::find_if(nodes.begin(), nodes.end(), [&](const auto& node) { return node->getKey() == key; });
	
    (*itNode)->setAsVisited();

    auto itNeighbours = std::find_if(adjacency.begin(), adjacency.end(), [&](const auto& vec) { return vec[0] == key; });

    std::vector<char>::iterator it = itNeighbours->begin();
    std::advance(it, 1);
    while (it != itNeighbours->end()) {
        auto itNode = std::find_if(nodes.begin(),nodes.end(), [&](const auto& node) { return node->getKey() == *it; });        
        if ((*itNode).get()->isVisited() == false) {
            nodesQueue.push(*it);
            (*itNode).get()->setAsVisited();
        }
        it++;
    }    
    
    nodesQueue.pop();    
}

