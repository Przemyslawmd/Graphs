
#include "dijkstra.h"


Dijkstra::Dijkstra(Graph& graph) : graph(graph) {}


void Dijkstra::traverseGraph(char srcKey)
{
    const auto& nodes = graph.getNodes();
    const auto& adjacency = graph.getAdjacency();
    
    if (routes.empty() == false) {
        routes.clear(); 
    }
    for (const auto& node : nodes) {
        int distance = node->getKey() == srcKey ? 0 : INT_MAX;
        routes[node->getKey()] = route{ distance };
    }

    std::optional<char> key = findNodeToProcess();
    while (key != std::nullopt) {
        graph.setNodeVisit(key.value(), true);
        processRoutesTable(adjacency, key.value());
        key = findNodeToProcess();
    }
    graph.resetVisitNodes();
}


void Dijkstra::processRoutesTable(const std::map<char, std::list<Edge>>& adjacency, char key)
{
    if (adjacency.count(key) != 1) {
        return;
    }
    auto& adjacentNodes = adjacency.at(key);

    for (auto node = adjacentNodes.begin(); node != adjacentNodes.end(); node++) {
        if (graph.isNodeVisited(node->dst) == false) {
            if (routes[node->dst].distance > routes[key].distance + node->weight)
            routes[node->dst] = route{ node->weight + routes[key].distance, std::optional<char>{ key }};
        }
    }   
}


std::optional<char> Dijkstra::findNodeToProcess()
{
    int initial = INT_MAX;
    std::optional<char> key;
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

