
#include "Node.h"

Node::Node(char key)
{
    this->key = key;
    state = State::NOT_VISITED;
}


char Node::getKey()
{
    return key;
}


void Node::setState(State state)
{
    this->state = state;
}


State Node::getState()
{
    return state;
}

