
#include "graph.h"


Graph::~Graph() {}


const std::vector<std::unique_ptr<Node>>& Graph::getNodes()
{
    return nodes;
}


void Graph::addNode(char key)
{
    if (isNodeExist(key) == false) {
        nodes.push_back(std::make_unique<Node>(key));
    }
}


bool Graph::isNodeExist(char key)
{
    return std::find_if(nodes.begin(), nodes.end(), [key](const auto& node) { return node.get()->getKey() == key; }) != nodes.end();    
}


void Graph::resetNodes()
{
    for (auto& node : nodes) {
        node->setVisited(false);
    }
}

