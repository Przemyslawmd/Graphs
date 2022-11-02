
#include "dijkstra.h"

#include <queue>


void Dijkstra::traverseGraph(GraphList& graph)
{
    const auto& nodes = graph.getNodes();
    auto& adjacency = graph.getAdjacency();
    
    for (const auto& node : nodes) {
        directionTable[node->getKey()] = direction{ INT_MAX, '\0' };
    }

    std::queue<char> nodesQueue {};
    nodesQueue.push(adjacency.begin()->first);
    
    while (!nodesQueue.empty()) {
        processQueue(adjacency, nodes);
    }
}


void Dijkstra::processQueue(std::map<char, std::list<Edge>>& adjacency, const std::vector<std::unique_ptr<Node>>& nodes)
{

}

