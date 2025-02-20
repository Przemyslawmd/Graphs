
#ifndef GRAPHS_GRAPH_CLIENT_H
#define GRAPHS_GRAPH_CLIENT_H

#include "graph/graph.h"

#include <memory>
#include <optional>
#include <tuple>
#include <string>
#include <vector>


class GraphClient
{
public:

    GraphClient(bool isDirected);

    void resetGraph(bool isDirected);

    void addNode(char key);
    void addNodes(const std::vector<char>& keys);

    void removeNode(char key);

    void addEdge(char src, char dst);
    void addEdgeWeighted(char src, char dst, size_t weight);

    void removeEdge(char src, char dst);

    void addEdges(char src, const std::vector<char>& dst);
    void addEdgesWeighted(char src, const std::vector<std::tuple<char, size_t>>& edges);

    std::unique_ptr<std::vector<char>> traverseBFS(char src);
    std::unique_ptr<std::vector<char>> traverseDFS(char src);

    std::unique_ptr<std::vector<char>> findShortestPath(char src, char dst);
    std::unique_ptr<std::vector<std::tuple<char, char>>> findMinSpanningTree();

    std::optional<std::string> getLastErrorMessage();

private:

    std::unique_ptr<Graph> graph;
};

#endif

