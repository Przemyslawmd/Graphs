
#ifndef GRAPHS_DIJKSTRA_H
#define GRAPHS_DIJKSTRA_H

#include "../graph/node.h"
#include "../graph/graphList.h"

 
typedef struct 
{
    int distance;
    char predecessor;
} direction;


class Dijkstra
{
public:

    Dijkstra() = default;
    Dijkstra(const Dijkstra&) = delete;
    Dijkstra& operator=(Dijkstra&) = delete;

    void traverseGraph(GraphList&);

private:

    void processQueue(std::map<char, std::list<std::tuple<char, int>>>& adjacency, const std::vector<std::unique_ptr<Node>>& nodes);
    
    std::map<char, direction> directionTable;
};

#endif

