
#ifndef GRAPHS_NODE_H
#define GRAPHS_NODE_H

#include <cstdint>
#include <optional>


class Node
{
public:

    explicit Node(char key);

    bool isVisited() const;
    void setVisited(bool isVisited);

    char key;
    std::optional<uint16_t> colour;

private:

    bool visited;
};

#endif

