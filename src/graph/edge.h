
#ifndef GRAPHS_EDGE_H
#define GRAPHS_EDGE_H


class Edge
{
public:

    Edge(char src, char dst, int weight) : src(src), dst(dst), weight(weight) {}

    bool operator==(const Edge& edge);

    const char src;
    const char dst;
    const int weight;
};

#endif

