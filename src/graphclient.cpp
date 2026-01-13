
#include "graphclient.h"

#include "algo/bfs.h"
#include "algo/dfs.h"
#include "algo/color.h"
#include "algo/dijkstra.h"
#include "algo/kruskal.h"
#include "logs/logCollector.h"


GraphClient::GraphClient(bool isDirected) : graph(std::make_unique<Graph>(isDirected)) {}


void GraphClient::resetGraph(bool isDirected)
{
    graph.reset();
    graph = std::make_unique<Graph>(isDirected);
}


void GraphClient::addNode(char key)
{
    graph->addNode(key);
}


void GraphClient::addNodes(const std::vector<char>& keys)
{
    graph->addNodes(keys);
}


void GraphClient::removeNode(char key)
{
    graph->removeNode(key);
}


void GraphClient::removeNodes(std::unique_ptr<std::vector<char>>& keys)
{
    for (char key : *keys) {
        graph->removeNode(key);
    }
}


void GraphClient::addEdge(char src, char dst)
{
    graph->addEdge(src, dst);
}


void GraphClient::addEdgeWeighted(char src, char dst, size_t weight)
{
    graph->addEdgeWeighted(src, dst, weight);
}


void GraphClient::addEdges(char src, const std::vector<char>& dst)
{
    graph->addEdges(src, dst);
}


void GraphClient::addEdgesWeighted(char src, const std::vector<std::tuple<char, size_t>>& edges)
{
    graph->addEdgesWeighted(src, edges);
}


void GraphClient::removeEdge(char src, char dst)
{
    graph->removeEdge(src, dst);
}


void GraphClient::removeEdges(std::unique_ptr<std::vector<std::tuple<char, char>>> edges)
{
    for (const auto& edge : *edges) {
        graph->removeEdge(std::get<0>(edge), std::get<1>(edge));
    }
}


std::unique_ptr<std::vector<char>> GraphClient::traverseBFS(char src)
{
    BFS bfs{ *graph };
    return bfs.traverseGraph(src);
}


std::unique_ptr<std::vector<char>> GraphClient::traverseDFS(char src)
{
    DFS dfs{ *graph };
    return dfs.traverseGraph(src);
}


std::unique_ptr<std::vector<char>> GraphClient::findShortestPath(char src, char dst)
{
    const auto nodes = std::make_unique<std::list<char>>();
    nodes->push_front(dst);
    Dijkstra dijkstra{ *graph };
    dijkstra.traverseGraph(src);
    const auto& routes = dijkstra.getRoutes();

    if (routes.at(dst).distance == INT_MAX) {
        LogCollector::putError(Error::NO_ROUTE);
        return nullptr;
    }

    std::optional<char> predecessor;
    predecessor = routes.at(dst).predecessor;
    while (predecessor != std::nullopt) {
        nodes->push_front(predecessor.value());
        predecessor = routes.at(predecessor.value()).predecessor;
    }
    return std::make_unique<std::vector<char>>(nodes->begin(), nodes->end());
}


std::unique_ptr<std::vector<std::tuple<char, char>>> GraphClient::findMinSpanningTree()
{
    Kruskal kruskal{ *graph };
    const auto edges = kruskal.makeMinSpanningTree();
    auto edgesAsChars = std::make_unique<std::vector<std::tuple<char, char>>>();

    for (const Edge& edge : *edges) {
        edgesAsChars->emplace_back(edge.src, edge.dst);
    }

    return edgesAsChars;
}


std::unique_ptr<std::vector<std::tuple<char, uint16_t>>> GraphClient::colorGraph()
{
    if (graph->isEmpty()) {
        LogCollector::putError(Error::NO_GRAPH);
        return nullptr;
    }

    Color color{ *graph };
    color.colorGraph();

    auto colors = std::make_unique<std::vector<std::tuple<char, uint16_t>>>();
    for (const auto& node : graph->getNodes()) {
        colors->emplace_back(node.getKey(), node.color);
    }
    return colors;
}


void GraphClient::resetColors()
{
    if (graph->isEmpty()) {
        LogCollector::putError(Error::NO_GRAPH);
        return;
    }
    graph->resetColors();
}


std::optional<std::string> GraphClient::getLastErrorMessage()
{
    return LogCollector::getLastMessage();
}

