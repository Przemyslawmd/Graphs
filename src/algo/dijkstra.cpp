
#include "dijkstra.h"

#include <climits>


Dijkstra::Dijkstra(Graph& graph) : graph(graph) {}


void Dijkstra::traverseGraph(char srcKey)
{
    const auto& nodes = graph.getNodes();
    const auto& adjacency = graph.getAdjacency();
    graph.setAllNodesAsNotVisited();

    if (routes.empty() == false) {
        routes.clear(); 
    }
    for (const auto& node : nodes) {
        int distance = node->key == srcKey ? 0 : INT_MAX;
        routes.emplace(node->key, route{ distance });
    }

    std::optional<char> key = findNodeToProcess();
    while (key != std::nullopt) {
        graph.setNodeAsVisited(key.value());
        processRoutesTable(adjacency, key.value());
        key = findNodeToProcess();
    }
}


void Dijkstra::processRoutesTable(const std::map<char, std::list<Edge>>& adjacency, char key)
{
    if (adjacency.count(key) != 1) {
        return;
    }

    const auto& adjacentNodes = adjacency.at(key);
    for (const auto& edge : adjacentNodes) {
        int currentWeight = routes[key].distance + edge.weight;
        if (graph.isNodeVisited(edge.dst) == false && routes[edge.dst].distance > currentWeight) {
            routes[edge.dst] = route{ currentWeight, std::optional<char>{ key }};
        }
    }   
}


std::optional<char> Dijkstra::findNodeToProcess()
{
    int initial = INT_MAX;
    std::optional<char> nodeToProcess;
    for (const auto& [nodeKey, route] : routes) {
        if (graph.isNodeVisited(nodeKey) == false && route.distance < initial) {
            initial = route.distance;
            nodeToProcess = nodeKey;
        }
    } 
    return nodeToProcess;
}


const std::map<char, route>& Dijkstra::getRoutes()
{
    return routes;
}

