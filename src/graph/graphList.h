
#ifndef GRAPHS_GRAPHLIST_H
#define GRAPHS_GRAPHLIST_H

#include "graph.h"
#include "node.h"

#include <list>
#include <map>
#include <memory>
#include <tuple>
#include <vector>


class GraphList : public Graph
{
public:
    
    virtual ~GraphList() {};
    GraphList() = default;
    GraphList(const std::vector<std::vector<char>>& adjacency);
    GraphList(const GraphList&) = delete;
    GraphList& operator=(GraphList&) = delete;

    void addEdge(char key1, char key2);
    void addNodes(std::vector<char>& nodeKeys);

    std::map<char, std::list<std::tuple<char, int>>>& getAdjacency();

private:

    std::map<char, std::list<std::tuple<char, int>>> adjacency;
};

#endif

