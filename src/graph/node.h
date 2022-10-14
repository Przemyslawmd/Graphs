
#ifndef GRAPHS_NODE_H
#define GRAPHS_NODE_H


class Node
{
public:
    
    explicit Node(char key);
    Node(const Node&) = delete;
    Node& operator=(Node&) = delete;

    char getKey() const;
    bool isVisited() const;
    void setAsVisited();

protected:

    char key;
    bool visited;
};       

#endif

