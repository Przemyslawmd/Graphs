
#include "node.h"


Graphs::Node::Node(char key) : key(key), visited(false) {}


bool Graphs::Node::isVisited() const
{
    return visited;
}


void Graphs::Node::setVisited(bool isVisited)
{
    visited = isVisited;
}

