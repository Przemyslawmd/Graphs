
#ifndef GRAPHS_GRAPH_CLIENT_H
#define GRAPHS_GRAPH_CLIENT_H

#include "algo/dijkstra.h"
#include "graph/graph.h"

#include <map>
#include <tuple>


class GraphClient
{
public:

    GraphClient();

    void addNode(char key);
    void addNodes(const std::vector<char>& keys);

    void addEdges(char srcKey, const std::vector<char>& dstKeys);
    void addEdgesWithWeight(char srcKey, const std::vector<std::tuple<char, int>>& edges);

    std::unique_ptr<std::vector<char>> findShortestPath(char src, char dst);

private:

    std::unique_ptr<Graph> graph;
};

#endif

