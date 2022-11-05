
#ifndef GRAPHS_DIJKSTRA_H
#define GRAPHS_DIJKSTRA_H

#include "../graph/edge.h"
#include "../graph/node.h"
#include "../graph/graphList.h"

 
typedef struct 
{
    int distance;
    char predecessor;
} route;


class Dijkstra
{
public:

    Dijkstra(GraphList&);
    Dijkstra(const Dijkstra&) = delete;
    Dijkstra& operator=(Dijkstra&) = delete;

    void traverseGraph(char srcKey);
    const std::map<char, route>& getRoutes();

private:

    void processRoutesTable(std::map<char, std::list<Edge>>& adjacency, const std::vector<std::unique_ptr<Node>>& nodes, char key);
    char findNodeToProcess();
    
    GraphList& graph;
    std::map<char, route> routes;
};

#endif

