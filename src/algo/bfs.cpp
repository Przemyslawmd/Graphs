
#include "bfs.h"

#include <iterator>


void BFS::traverseGraph(GraphList& graph)
{
    const auto& nodes = graph.getNodes();
    auto& adjacency = graph.getAdjacency();
    
    nodesQueue.push(adjacency.begin()->first);
    
    while (!nodesQueue.empty()) {
        processQueue(adjacency, nodes);
    }
}

void BFS::processQueue(std::map<char, std::list<Edge>>& adjacency, const std::vector<std::unique_ptr<Node>>& nodes)
{
    char key = nodesQueue.front();
    auto node = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node->getKey() == key; });
    (*node)->setVisited(true);

    auto& neighbours = adjacency[key];

    auto it = neighbours.begin();
    while (it != neighbours.end()) {
        auto neighbour = std::find_if(nodes.begin(), nodes.end(), [it](const auto& node) { return node->getKey() == it->dstKey; });        
        if ((*neighbour).get()->isVisited() == false) {
            nodesQueue.push(it->dstKey);
            (*neighbour).get()->setVisited(true);
        }
        it++;
    }    
    
    nodesQueue.pop();  
}

