
#include "graph/graph.h"


enum class GraphType {
    Unweighted_FourNodes,
    Unweighted_FiveNodes,               // A graph on a picture
    Unweighted_SevenNodes,              // B
    Unweighted_FourteenNodes,           // C
    Unweighted_TwentyNodes,
    Weighted_EightNodes,
    Weighted_NineNodes_Nondirectorial,
    Weighted_TenNodes_Nondirectorial,
    Weighted_TwelveNodes,
    TwoConnectedDiamonds,                // D
    SixteenNodes_A,                      // Sixteen_A
    SixteenNodes_B,                      // Sixteen_B
    SixteenNodes_C,                      // Sixteen_C
};


class GraphFactory
{
public:

    static void createGraph(Graph& graph, GraphType type)
    {
        switch(type)
        {
            case GraphType::Unweighted_FourNodes:
                graph.addEdges('a', { 'b' });
                graph.addEdges('b', { 'c', 'd' });
                graph.addEdges('c', { 'a', 'b', 'd' });
                graph.addEdges('d', { 'c' });
                break;
            case GraphType::Unweighted_FiveNodes:
                graph.addEdges('a', { 'b' });
                graph.addEdges('b', { 'a', 'c' });
                graph.addEdges('c', { 'b', 'd', 'e' });
                graph.addEdges('d', { 'c' });
                graph.addEdges('e', { 'd' });
                break;
            case GraphType::Unweighted_SevenNodes:
                graph.addEdges('a', { 'b', 'd' });
                graph.addEdges('b', { 'a', 'c', 'd', 'g' });
                graph.addEdges('c', { 'b', 'g' });
                graph.addEdges('d', { 'a', 'b', 'f' });
                graph.addEdges('e', { 'f' });
                graph.addEdges('f', { 'd', 'e' });
                graph.addEdges('g', { 'b', 'c' });
                break;
            case GraphType::Unweighted_FourteenNodes:
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
                break;
            case GraphType::Unweighted_TwentyNodes:
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
                break;
            case GraphType::Weighted_EightNodes:
                graph.addEdgesWeighted('a', {{ 'd', 3 }, { 'h', 5 }});
                graph.addEdgesWeighted('b', {{ 'c', 4 } });
                graph.addEdgesWeighted('c', {{ 'a', 4 } });
                graph.addEdgesWeighted('d', {{ 'b', 2 }, { 'e', 1 }, { 'f', 8 }});
                graph.addEdgesWeighted('e', {{ 'c', 5 } });
                graph.addEdgesWeighted('f', {{ 'e', 2 }, { 'h', 2 } });
                graph.addEdgesWeighted('g', {{ 'e', 3 } });
                graph.addEdgesWeighted('h', {{ 'g', 6 } });
                break;
            case GraphType::Weighted_NineNodes_Nondirectorial:
                graph.addEdgesWeighted('a', {{ 'b', 4 }, { 'h', 8 }});
                graph.addEdgesWeighted('b', {{ 'c', 9 }, { 'h', 11 }});
                graph.addEdgesWeighted('c', {{ 'd', 7 }, { 'f', 4 },  { 'i', 2 }});
                graph.addEdgesWeighted('d', {{ 'e', 9 }, { 'f', 14 }});
                graph.addEdgesWeighted('e', {{ 'f', 10 } });
                graph.addEdgesWeighted('f', {{ 'g', 2 } });
                graph.addEdgesWeighted('g', {{ 'h', 1 }, {'i', 6 }});
                graph.addEdgesWeighted('h', {{ 'i', 7 } });
                break;
            case GraphType::Weighted_TenNodes_Nondirectorial:
                graph.addEdgesWeighted('a', {{ 'b', 3 }, { 'f', 2 }});
                graph.addEdgesWeighted('b', {{ 'c', 17 }, { 'd', 16 }});
                graph.addEdgesWeighted('c', {{ 'd', 8 }, { 'i', 18 }});
                graph.addEdgesWeighted('d', {{ 'e', 11 }, { 'i', 4 }});
                graph.addEdgesWeighted('e', {{ 'f', 1 }, { 'g', 6 }, { 'h', 5 }, { 'i', 10 }});
                graph.addEdgesWeighted('f', {{ 'g', 7 }});
                graph.addEdgesWeighted('g', {{ 'h', 15 }});
                graph.addEdgesWeighted('h', {{ 'i', 12 }, { 'j', 13 }});
                graph.addEdgesWeighted('i', {{ 'j', 9 }});
                break;
            case GraphType::Weighted_TwelveNodes:
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
                break;
            case GraphType::TwoConnectedDiamonds:
                graph.addEdges('a', { 'b', 'd' });
                graph.addEdges('b', { 'a', 'c', 'd', 'f' });
                graph.addEdges('c', { 'b', 'd' });
                graph.addEdges('d', { 'a', 'b', 'c', 'h' });
                graph.addEdges('e', { 'f', 'g', 'h' });
                graph.addEdges('f', { 'b', 'e', 'g' });
                graph.addEdges('g', { 'e', 'f', 'h' });
                graph.addEdges('h', { 'd', 'e', 'g' });
                break;
            case GraphType::SixteenNodes_A:
                graph.addEdges('a', { 'b', 'c', 'e', 'f', 'g', 'j' });
                graph.addEdges('b', { 'a', 'c', 'd', 'g', 'h', 'n' });
                graph.addEdges('c', { 'a', 'b', 'd', 'i', 'j', 'o' });
                graph.addEdges('d', { 'b', 'c', 'h', 'i', 'k', 'l' });
            
                graph.addEdges('e', { 'a', 'f', 'g', 'i', 'k', 'm' });
                graph.addEdges('f', { 'a', 'e', 'h', 'j', 'l', 'm' });
                graph.addEdges('g', { 'a', 'b', 'e', 'k', 'n', 'p' });
                graph.addEdges('h', { 'b', 'd', 'f', 'l', 'm', 'n' });

                graph.addEdges('i', { 'c', 'd', 'e', 'k', 'm', 'o' });
                graph.addEdges('j', { 'a', 'c', 'f', 'l', 'o', 'p' });
                graph.addEdges('k', { 'd', 'e', 'g', 'i', 'l', 'p' });
                graph.addEdges('l', { 'd', 'f', 'h', 'j', 'k', 'p' });

                graph.addEdges('m', { 'e', 'f', 'h', 'i', 'n', 'o' });
                graph.addEdges('n', { 'b', 'g', 'h', 'm', 'o', 'p' });
                graph.addEdges('o', { 'c', 'i', 'j', 'm', 'n', 'p' });
                graph.addEdges('p', { 'g', 'j', 'k', 'l', 'n', 'o' });
                break;
            case GraphType::SixteenNodes_B:
                graph.addEdges('a', { 'b', 'c', 'g', 'j' });
                graph.addEdges('b', { 'a', 'c', 'd', 'g', 'h', 'n' });
                graph.addEdges('c', { 'a', 'b', 'd', 'i', 'j', 'o' });
                graph.addEdges('d', { 'b', 'c', 'h', 'i' });
            
                graph.addEdges('e', { 'f', 'i', 'k' });
                graph.addEdges('f', { 'e', 'h', 'l' });
                graph.addEdges('g', { 'a', 'b', 'n', 'p' });
                graph.addEdges('h', { 'b', 'd', 'f', 'l', 'm', 'n' });

                graph.addEdges('i', { 'c', 'd', 'e', 'k', 'm', 'o' });
                graph.addEdges('j', { 'a', 'c', 'o', 'p' });
                graph.addEdges('k', { 'e', 'i', 'l' });
                graph.addEdges('l', { 'f', 'h', 'k' });

                graph.addEdges('m', { 'h', 'i', 'n', 'o' });
                graph.addEdges('n', { 'b', 'g', 'h', 'm', 'o', 'p' });
                graph.addEdges('o', { 'c', 'i', 'j', 'm', 'n', 'p' });
                graph.addEdges('p', { 'g', 'j', 'n', 'o' });
                break;
            case GraphType::SixteenNodes_C:
                graph.addEdges('a', { 'b', 'c', 'g', 'j' });
                graph.addEdges('b', { 'a', 'd', 'g', 'h' });
                graph.addEdges('c', { 'a', 'd', 'i', 'j' });
                graph.addEdges('d', { 'b', 'c', 'h' });
            
                graph.addEdges('e', { 'f', 'i', 'k' });
                graph.addEdges('f', { 'e', 'l' });
                graph.addEdges('g', { 'a', 'b', 'n', 'p' });
                graph.addEdges('h', { 'b', 'd', 'm', 'n' });

                graph.addEdges('i', { 'c', 'e', 'k', 'o' });
                graph.addEdges('j', { 'a', 'c', 'o', 'p' });
                graph.addEdges('k', { 'e', 'i', 'l' });
                graph.addEdges('l', { 'f', 'k' });

                graph.addEdges('m', { 'h', 'n', 'o' });
                graph.addEdges('n', { 'g', 'h', 'm', 'p' });
                graph.addEdges('o', { 'i', 'j', 'm', 'p' });
                graph.addEdges('p', { 'g', 'j', 'n', 'o' });
                break;
        }
    }
};

