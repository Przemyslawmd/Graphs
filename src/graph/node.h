
#ifndef GRAPHS_NODE_H
#define GRAPHS_NODE_H

#include <cstdint>
#include <optional>


class Node
{
public:

    explicit Node(char key)
    : key{key}, visited{false}, color{0} {};

    const char getKey() const
    {
        return key;
    };

    bool isVisited() const
    {
        return visited;
    };

    void setVisited(bool isVisited)
    {
        visited = isVisited;
    };

    uint16_t color;

private:

    char key;
    bool visited;
};

#endif

