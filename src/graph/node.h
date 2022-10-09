
#ifndef GRAPHS_NODE_H
#define GRAPHS_NODE_H


enum class State
{
    NOT_VISITED,
    VISITED,
    COMPLETED
};


class Node
{
public:
    
    explicit Node(char key);

    char getKey();
    void setState(State state);
    State getState();

protected:

    char key;
    State state;
};       

#endif

