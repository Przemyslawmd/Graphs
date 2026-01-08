
#ifndef GRAPHS_COLOUR_H
#define GRAPHS_COLOUR_H

#include <map>
#include <queue>

#include "graph/graph.h"


class Color
{
public:

    explicit Color(Graph&);
    Color(const Color&) = delete;
    Color(Color&&) = delete;
    Color& operator=(const Color&) = delete;
    Color& operator=(Color&&) = delete;

    void colorGraph();

private:

    void processQueue(const std::map<char, std::list<Edge>>&);

    Graph& graph;
    std::map<uint16_t, bool> colorPool;
    std::queue<char> nodesQueue;
};

#endif

