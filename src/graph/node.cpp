
#include "Node.h"


Node::Node(char key)
{
    this->key = key;
    visited = false;
}


char Node::getKey() const
{
    return key;
}


bool Node::isVisited() const
{
    return visited;
}


void Node::setVisited(bool isVisited)
{
    visited = isVisited;
}

