#include <iostream>
#include <algorithm>
#include "Util.h"
#include "MST.h"
using namespace std;
int main()
{
    int vertexNum = 6;
    int edgeNum = 10;
    AdjList graph(vertexNum);
    AdjList mstPrim(vertexNum);
    AdjList mstKruskal(vertexNum);
    vector<Edge> edges;
    Util::CreateRandomGraph(vertexNum, edgeNum, edges);
    cout << "Grafo aleatorio" << endl;
    for (Edge edge : edges)
        cout << "(" << (char)(edge.v + 65) << "," << (char)(edge.w+65) << "," << edge.weight << "),";
    cout << endl;
    graph.LoadEdges(edges);
    graph.Export("original.txt");
    MST::Kruskal(graph,vertexNum, mstKruskal);
    MST::Prim(graph, vertexNum ,0,mstPrim);
    return 1;
}