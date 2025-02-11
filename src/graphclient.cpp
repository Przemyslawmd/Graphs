
#include "graphclient.h"
#include "algo/bfs.h"
#include "algo/dfs.h"
#include "algo/dijkstra.h"
#include "algo/kruskal.h"


GraphClient::GraphClient(bool isDirected) : graph(std::make_unique<Graph>(isDirected)) {}


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
    const auto nodesList = std::make_unique<std::list<char>>();
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


std::unique_ptr<std::vector<std::tuple<char, char>>> GraphClient::findMinSpanningTree()
{
    Kruskal kruskal{ *(graph.get()) };
    auto edges = kruskal.makeMinSpanningTree();
    auto edgesTuple  = std::make_unique<std::vector<std::tuple<char, char>>>();

    for (const Edge& edge : *edges) {
        edgesTuple->push_back(std::tuple<char, char>{ edge.src, edge.dst });
    }

    return edgesTuple;
}

