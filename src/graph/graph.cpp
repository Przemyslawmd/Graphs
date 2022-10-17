
#include "graph.h"


Graph::~Graph() {}


std::vector<std::unique_ptr<Node>>& Graph::getNodes()
{
    return nodes;
}

