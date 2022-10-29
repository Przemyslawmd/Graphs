
#include "bfs.h"

#include <iterator>


void BFS::traverseGraph(GraphList& graph)
{
    auto& nodes = graph.getNodes();
    auto& adjacency = graph.getAdjacency();
    
    nodesQueue.push(adjacency.begin()->first);
    
    while (!nodesQueue.empty()) {
        processQueue(adjacency, nodes);
    }
}


void BFS::processQueue(std::map<char, std::list<std::tuple<char, int>>>& adjacency, std::vector<std::unique_ptr<Node>>& nodes)
{
    char key = nodesQueue.front();
    auto node = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node->getKey() == key; });
    (*node)->setAsVisited();    

    auto& neighbours = adjacency[key];

    auto it = neighbours.begin();
    while (it != neighbours.end()) {
        auto neighbour = std::find_if(nodes.begin(), nodes.end(), [it](const auto& node) { return node->getKey() == std::get<0>(*it); });        
        if ((*neighbour).get()->isVisited() == false) {
            nodesQueue.push(std::get<0>(*it));
            (*neighbour).get()->setAsVisited();
        }
        it++;
    }    
    
    nodesQueue.pop();  
}

