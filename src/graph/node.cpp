
#include "Node.h"


Node::Node(char key)
{
    this->key = key;
    visited = false;
}


char Node::getKey()
{
    return key;
}


bool Node::isVisited()
{
    return visited;
}


void Node::setAsVisited()
{
    visited = true;
}

