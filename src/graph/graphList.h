
#ifndef GRAPHS_GRAPHLIST_H
#define GRAPHS_GRAPHLIST_H

#include "graph.h"
#include "node.h"

#include <list>
#include <map>
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
        
    void addEdges(char srcKey, const std::vector<char>& dstKeys);
    void addNodes(const std::vector<char>& nodeKeys);

    std::map<char, std::list<std::tuple<char, int>>>& getAdjacency();

private:

    void addEdge(char srcKey, char dstKey);
    
    std::map<char, std::list<std::tuple<char, int>>> adjacency;
};

#endif

