
#ifndef GRAPHS_NODE_H
#define GRAPHS_NODE_H

#include <cstdint>


class Node
{
public:

    explicit Node(char key) : key{ key }, visited{ false }, color{ 0 } {};

    const char getKey() const
    {
        return key;
    };

    uint8_t color;
    bool visited;

private:

    char key;
};

#endif

