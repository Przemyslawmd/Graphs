
#include "graph.h"


Graph::~Graph() {}


std::vector<std::unique_ptr<Node>>& Graph::getNodes()
{
    return nodes;
}


void Graph::addNode(char key)
{
    if (std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.get()->getKey() == key; } ) == nodes.end()) {
        nodes.push_back(std::make_unique<Node>(key));
    }
}

