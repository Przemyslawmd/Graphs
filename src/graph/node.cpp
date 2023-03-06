
#include "node.h"


Node::Node(char key) : key(key), visited(false) {}


bool Node::isVisited() const
{
    return visited;
}


void Node::setVisited(bool isVisited)
{
    visited = isVisited;
}

