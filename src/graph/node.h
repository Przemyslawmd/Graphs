
#ifndef GRAPHS_NODE_H
#define GRAPHS_NODE_H


class Node
{
public:
    
    explicit Node(char key);

    char getKey();
    bool isVisited();
    void setAsVisited();

protected:

    char key;
    bool visited;
};       

#endif

