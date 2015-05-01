#include "edge.h"

Edge::Edge()
{

}

Edge::Edge(Vec4* from, Vec4* to)
{
    vertexs[0] = from;
    vertexs[1] = to;
}
