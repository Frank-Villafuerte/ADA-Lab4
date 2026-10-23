#include "MST.h"
#include <iostream>
using namespace std;
int main()
{
    vector<Edge> edges = { {0,1,6} ,{0,2,3} ,{0,4,4} ,{1,2,4} ,{1,3,3} ,{2,3,2} ,{2,4,5} ,{3,5,6} ,{3,6,5} ,{4,5,3} ,{4,7,2} ,{4,8,5} ,{5,6,4} ,{5,7,2} ,{6,9,3} ,{7,8,2} ,{7,9,5} ,{8,9,4} };
    AdjList graph(10);
    AdjList mstKruskal(10);
    AdjList mstPrim(10);
    graph.LoadEdges(edges);
    graph.Export("graph.txt");
    MST::Kruskal(graph, 10, mstKruskal);
    MST::Prim(graph, 10,5, mstPrim);
    mstKruskal.Export("kruskal.txt");
    mstPrim.Export("prim.txt");
    return 1;
}