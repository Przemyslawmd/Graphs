
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

    char key = findNodeToProcess();
    while (key != '\0') {
        graph.setNodeVisit(key, true);
        processRoutesTable(adjacency, key);
        key = findNodeToProcess();
    }
}


void Dijkstra::processRoutesTable(std::map<char, std::list<Edge>>& adjacency, char key)
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

