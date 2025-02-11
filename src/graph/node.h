
#ifndef GRAPHS_NODE_H
#define GRAPHS_NODE_H


class Node
{
public:

    explicit Node(char key);

    bool isVisited() const;
    void setVisited(bool isVisited);

    char key;

private:

    bool visited;
};

#endif

