
#include "../src/graph/graph.h"


enum class GraphType {
    Unweighted_FiveNodes,
    Unweighted_SevenNodes,
    Unweighted_FourteenNodes,
    Unweighted_TwentyNodes,
};


class GraphFactory
{
public:

    static void createGraph(Graph& graph, GraphType type)
    {   
        if (type == GraphType::Unweighted_FiveNodes) {
            graph.addEdges('a', { 'b' });
            graph.addEdges('b', { 'a', 'c' });
            graph.addEdges('c', { 'b', 'd', 'e' });
            graph.addEdges('d', { 'c', 'e' });
            graph.addEdges('e', { 'c', 'd' });
        }
        else if (type == GraphType::Unweighted_SevenNodes) {
            graph.addEdges('a', { 'b', 'd' });
            graph.addEdges('b', { 'a', 'c', 'd', 'g' });
            graph.addEdges('c', { 'b', 'g' });
            graph.addEdges('d', { 'a', 'b', 'f' });
            graph.addEdges('e', { 'f' });
            graph.addEdges('f', { 'd', 'e' });
            graph.addEdges('g', { 'b', 'c' });
        }
        else if (type == GraphType::Unweighted_FourteenNodes) {
            graph.addEdges('a', { 'd', 'h' });
            graph.addEdges('b', { 'c' });
            graph.addEdges('c', { 'a', 'i' });
            graph.addEdges('d', { 'b', 'e', 'f' });
            graph.addEdges('e', { 'c' });
            graph.addEdges('f', { 'e', 'h', 'k' });
            graph.addEdges('g', { 'e', 'i' });
            graph.addEdges('h', { 'g', 'j' });
            graph.addEdges('i', { 'f', 'n' });
            graph.addEdges('j', { 'k' });
            graph.addEdges('k', { 'l' });
            graph.addEdges('l', { 'c', 'n' });
            graph.addEdges('m', { 'h', 'k' });
            graph.addEdges('n', { 'm' });
        }
        else if (type == GraphType::Unweighted_TwentyNodes) {
            graph.addEdges('a', { 'd', 'h' });
            graph.addEdges('b', { 'c' });
            graph.addEdges('c', { 'a', 'i' });
            graph.addEdges('d', { 'b', 'e', 'f' });
            graph.addEdges('e', { 'c' });
            graph.addEdges('f', { 'e', 'h', 'k' });
            graph.addEdges('g', { 'e', 'i', 'o' });
            graph.addEdges('h', { 'g', 'j' });
            graph.addEdges('i', { 'f', 'n', 'p' });
            graph.addEdges('j', { 'k' });
            graph.addEdges('k', { 'l' });
            graph.addEdges('l', { 'c', 'n' });
            graph.addEdges('m', { 'h', 'k' });
            graph.addEdges('n', { 'm' });
            graph.addEdges('o', { 'c', 'u' });
            graph.addEdges('p', { 'r', 's' });
            graph.addEdges('r', { 'g', 'i', 't' });
            graph.addEdges('s', { 'o', 'u' });
            graph.addEdges('t', { 'l', 'n' });
            graph.addEdges('u', { 'r' });
        }
    }
};

