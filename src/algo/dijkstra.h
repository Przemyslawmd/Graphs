
#ifndef GRAPHS_DIJKSTRA_H
#define GRAPHS_DIJKSTRA_H

#include "../graph/edge.h"
#include "../graph/node.h"
#include "../graph/graph.h"

#include <list>
#include <map>
#include <optional>
 

typedef struct 
{
    int distance;
    std::optional<char> predecessor;
} route;


class Dijkstra
{
public:

    explicit Dijkstra(Graph&);
    Dijkstra(const Dijkstra&) = delete;
    Dijkstra(Dijkstra&&) = delete;
    Dijkstra& operator=(const Dijkstra&) = delete;
    Dijkstra& operator=(Dijkstra&&) = delete;

    void traverseGraph(char srcKey);
    const std::map<char, route>& getRoutes();

private:

    void processRoutesTable(const std::map<char, std::list<Edge>>& adjacency, char key);
    std::optional<char> findNodeToProcess();
    
    Graph& graph;
    std::map<char, route> routes;
};

#endif

