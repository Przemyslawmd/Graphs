
#include "dijkstra.h"


Dijkstra::Dijkstra(GraphList& graph) : graph(graph) {}


void Dijkstra::traverseGraph(char srcKey)
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
        char key = findNodeToProcess();
        if (key == '\0') {
            break;
        }
        auto node = std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node->getKey() == key; }); 
        (*node)->setVisited(true);
        processRoutesTable(adjacency, nodes, key);
    }
}


void Dijkstra::processRoutesTable(std::map<char, std::list<Edge>>& adjacency, const std::vector<std::unique_ptr<Node>>& nodes, char key)
{
    auto& adjacentNodes = adjacency[key];

    for (auto node = adjacentNodes.begin(); node != adjacentNodes.end(); node++) {
        if (graph.isNodeVisited(node->dstKey) == false) {
            if (routes[node->dstKey].distance > routes[key].distance + node->weight)
            routes[node->dstKey] = route{ node->weight + routes[key].distance, key };
        }
    }   
}


char Dijkstra::findNodeToProcess()
{
    int initial = INT_MAX;
    char key = '\0';
    for (auto route = routes.begin(); route != routes.end(); route++) {
        if (graph.isNodeVisited(route->first) == false && route->second.distance < initial) {
            initial = route->second.distance;
            key = route->first;
        }
    } 
    return key;
}


const std::map<char, route>& Dijkstra::getRoutes()
{
    return routes;
}

