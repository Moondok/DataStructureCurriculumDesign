#include "innergraph.h"

InnerGraph::InnerGraph(QObject *parent) : QObject(parent),num(3)
{
    adjMatrix[0][1]=adjMatrix[1][0]=true;
    adjMatrix[0][2]=adjMatrix[2][0]=true;
}
