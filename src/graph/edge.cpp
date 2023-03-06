
#include "edge.h"


bool Edge::operator==(const Edge& edge) 
{
    return this->weight == edge.weight &&
           (
           (this->src == edge.src && this->dst == edge.dst) ||
           (this->src == edge.dst && this->dst == edge.src)
           );
}

