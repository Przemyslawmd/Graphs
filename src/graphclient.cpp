
#include "graphclient.h"
#include "algo/dijkstra.h"
#include "algo/kruskal.h"

#include <bits/stdc++.h>


GraphClient::GraphClient() : graph(std::make_unique<Graph>()) {}


void GraphClient::addNode(char key)
{
    graph->addNode(key);
}


void GraphClient::addNodes(const std::vector<char>& keys)
{
    graph->addNodes(keys);
}


void GraphClient::addEdges(char srcKey, const std::vector<char>& dstKeys)
{
    graph->addEdges(srcKey, dstKeys);
}


void GraphClient::addEdgesWithWeight(char srcKey, const std::vector<std::tuple<char, int>>& edges)
{
    graph->addEdgesWithWeight(srcKey, edges);
}


std::unique_ptr<std::vector<char>> GraphClient::findShortestPath(char src, char dst)
{
    auto nodesList = std::make_unique<std::list<char>>();
    nodesList->push_front(dst);
    Dijkstra dijkstra{ *(graph.get()) };
    dijkstra.traverseGraph(src);
    const std::map<char, route>& routes = dijkstra.getRoutes();

    std::optional<char> predecessor;
    predecessor = routes.at(dst).predecessor;
    while (predecessor != std::nullopt) {
        nodesList->push_front(predecessor.value());
        predecessor = routes.at(predecessor.value()).predecessor;
    }
    return std::make_unique<std::vector<char>>(nodesList->begin(), nodesList->end());
}


std::unique_ptr<std::vector<std::tuple<char, char>>> GraphClient::findMinimumSpanningTree()
{
    Kruskal kruskal{ *(graph.get()) };
    auto edges = kruskal.makeMinSpanningTree();
    auto edgesTuple  = std::make_unique<std::vector<std::tuple<char, char>>>();

    for (const Edge& edge : *edges) {
        edgesTuple->push_back(std::tuple<char, char>{ edge.src, edge.dst });
    }

    return edgesTuple;
}

