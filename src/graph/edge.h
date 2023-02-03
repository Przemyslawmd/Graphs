
#ifndef GRAPHS_EDGE_H
#define GRAPHS_EDGE_H


class Edge
{
public:

    Edge(char src, char dst, int weight) : src(src), dst(dst), weight(weight) {}

    bool isEqual(const Edge& edge) {
        return this->weight == edge.weight && 
               (
               (this->src == edge.src && this->dst == edge.dst) || 
               (this->src == edge.dst && this->dst == edge.src)
               );
    }

    char src;
    char dst;
    int weight;
};

#endif

