
#ifndef GRAPHS_COLOUR_H
#define GRAPHS_COLOUR_H


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

    Graph& graph;
};

#endif

