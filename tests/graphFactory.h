
#include "graph/graph.h"


enum class GraphType {
    Unweighted_FiveNodes,               // A graph on a picture
    Unweighted_SevenNodes,              // B
    Unweighted_FourteenNodes,
    Unweighted_TwentyNodes,
    Weighted_EightNodes,
    Weighted_NineNodes_Nondirectorial,
    Weighted_TenNodes_Nondirectorial,
    Weighted_TwelveNodes,
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
        else if (type == GraphType::Weighted_EightNodes) {
            graph.addEdgesWeighted('a', {{ 'd', 3 }, { 'h', 5 }});
            graph.addEdgesWeighted('b', {{ 'c', 4 } });
            graph.addEdgesWeighted('c', {{ 'a', 4 } });
            graph.addEdgesWeighted('d', {{ 'b', 2 }, { 'e', 1 }, { 'f', 8 }});
            graph.addEdgesWeighted('e', {{ 'c', 5 } });
            graph.addEdgesWeighted('f', {{ 'e', 2 }, { 'h', 2 } });
            graph.addEdgesWeighted('g', {{ 'e', 3 } });
            graph.addEdgesWeighted('h', {{ 'g', 6 } });
        }
        else if (type == GraphType::Weighted_NineNodes_Nondirectorial) {
            graph.addEdgesWeighted('a', {{ 'b', 4 }, { 'h', 8 }});
            graph.addEdgesWeighted('b', {{ 'c', 9 }, { 'h', 11 }});
            graph.addEdgesWeighted('c', {{ 'd', 7 }, { 'f', 4 },  { 'i', 2 }});
            graph.addEdgesWeighted('d', {{ 'e', 9 }, { 'f', 14 }});
            graph.addEdgesWeighted('e', {{ 'f', 10 } });
            graph.addEdgesWeighted('f', {{ 'g', 2 } });
            graph.addEdgesWeighted('g', {{ 'h', 1 }, {'i', 6 }});
            graph.addEdgesWeighted('h', {{ 'i', 7 } });
        }
        else if (type == GraphType::Weighted_TenNodes_Nondirectorial) {
            graph.addEdgesWeighted('a', {{ 'b', 3 }, { 'f', 2 }});
            graph.addEdgesWeighted('b', {{ 'c', 17 }, { 'd', 16 }});
            graph.addEdgesWeighted('c', {{ 'd', 8 }, { 'i', 18 }});
            graph.addEdgesWeighted('d', {{ 'e', 11 }, { 'i', 4 }});
            graph.addEdgesWeighted('e', {{ 'f', 1 }, { 'g', 6 }, { 'h', 5 }, { 'i', 10 }});
            graph.addEdgesWeighted('f', {{ 'g', 7 }});
            graph.addEdgesWeighted('g', {{ 'h', 15 }});
            graph.addEdgesWeighted('h', {{ 'i', 12 }, { 'j', 13 }});
            graph.addEdgesWeighted('i', {{ 'j', 9 }});
        }
        else if (type == GraphType::Weighted_TwelveNodes) {
            graph.addEdgesWeighted('a', {{ 'd', 3 }, { 'h', 5 }});
            graph.addEdgesWeighted('b', {{ 'c', 4 }, { 'i', 1 }});
            graph.addEdgesWeighted('c', {{ 'a', 4 }, { 'l', 5 }});
            graph.addEdgesWeighted('d', {{ 'b', 2 }, { 'e', 1 }, { 'f', 8 }});
            graph.addEdgesWeighted('e', {{ 'c', 5 }, { 'j', 7 }});
            graph.addEdgesWeighted('f', {{ 'e', 2 }, { 'h', 2 }, { 'i', 7 }, { 'k', 10 }});
            graph.addEdgesWeighted('g', {{ 'e', 3 }});
            graph.addEdgesWeighted('h', {{ 'g', 6 }, { 'l', 4 }});
            graph.addEdgesWeighted('i', {{ 'k', 6 }});
            graph.addEdgesWeighted('j', {{ 'c', 8 }});
            graph.addEdgesWeighted('k', {{ 'g', 3 }, { 'j', 5 }});
            graph.addEdgesWeighted('l', {{ 'g', 2 }, { 'e', 5 }, {'f', 12 }});
        }
    }
};

