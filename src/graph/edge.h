
#ifndef GRAPHS_EDGE_H
#define GRAPHS_EDGE_H


class Edge
{
public:

    Edge(char src, char dst, size_t weight) : src(src), dst(dst), weight(weight) {}

    bool operator==(const Edge& edge);

    const char src;
    char dst;
    const size_t weight;
};

#endif

