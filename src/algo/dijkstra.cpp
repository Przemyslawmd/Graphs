
#include "dijkstra.h"

#include <queue>
#include <iostream>

void Dijkstra::traverseGraph(GraphList& graph, char srcKey)
{
    const auto& nodes = graph.getNodes();
    auto& adjacency = graph.getAdjacency();
    
    if (routes.empty() == false) {
        routes.clear(); 
    }
    for (const auto& node : nodes) {
        int distance = node->getKey() == srcKey ? 0 : INT_MAX;
        routes[node->getKey()] = route{ distance, '\0' };
    }

    while (true) {
        char key = findNodeToProcess(routes, nodes);
        if (key == '\0') {
            break;
        }
        auto node = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node->getKey() == key; }); 
        (*node)->setVisited(true);
        processDirectionTable(adjacency, nodes, key);
    }
}


void Dijkstra::processDirectionTable(std::map<char, std::list<Edge>>& adjacency, const std::vector<std::unique_ptr<Node>>& nodes, char key)
{
    auto& adjacentNodes = adjacency[key];

    auto it = adjacentNodes.begin();
    while (it != adjacentNodes.end()) {
        auto node = std::find_if(nodes.begin(), nodes.end(), [it](const auto& node) { return node->getKey() == it->dstKey; });        
        if ((*node).get()->isVisited() == false) {
            if (routes[it->dstKey].distance > routes[key].distance + it->weight)
            routes[it->dstKey] = route{ it->weight + routes[key].distance, key };
        }
        it++;
    }   
}


char Dijkstra::findNodeToProcess(std::map<char, route>& table, const std::vector<std::unique_ptr<Node>>& nodes)
{
    std::cout << "Find Node to Process: Enter" << std::endl; 
    int initial = INT_MAX;
    char key = '\0';
    auto it = table.begin();
    while (it != table.end()) {
        auto itNode = std::find_if(nodes.begin(), nodes.end(), [it](const auto& node) { return node->getKey() == it->first; });    
        if (itNode->get()->isVisited() == false && it->second.distance < initial) {
            initial = it->second.distance;
            key = it->first;
        }
        it++;
    } 
    return key;
}


const std::map<char, route>& Dijkstra::getRoutes()
{
    return routes;
}

