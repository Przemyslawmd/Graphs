
#ifndef COLOR_H
#define COLOR_H

#include "../graph/graph.h"


class ColorGraph
{
public:

    explicit ColorGraph(Graph&);
    ColorGraph(const ColorGraph&) = delete;
    ColorGraph(ColorGraph&&) = delete;
    ColorGraph& operator=(const ColorGraph&) = delete;
    ColorGraph& operator=(ColorGraph&&) = delete;

private:

    Graph& graph;
};

#endif

