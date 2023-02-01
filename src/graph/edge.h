
#ifndef GRAPHS_EDGE_H
#define GRAPHS_EDGE_H


struct Edge 
{
    Edge(char src, char dst, int weight) : src(src), dst(dst), weight(weight) {}

    char src;
    char dst;
    int weight;
};

#endif

