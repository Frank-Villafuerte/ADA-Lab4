#include "AdjMatrix.h"
#include "AdjList.h"
#include <iostream>
#include <algorithm>
#include "Util.h"
#include "MST.h"
using namespace std;
int main()
{
    int vertexNum = 6;
    int edgeNum = 10;
    AdjMatrix matrix(vertexNum);
    AdjMatrix mstPrim(vertexNum);
    AdjMatrix mstKruskal(vertexNum);
    vector<Edge> edges;
    Util::CreateRandomGraph(vertexNum, edgeNum, edges);
    for (Edge edge : edges)
        cout << "(" << (char)(edge.v + 65) << "," << (char)(edge.w+65) << "," << edge.weight << "),";
    cout << endl;
    matrix.LoadEdges(edges);
    matrix.Export("original.txt");
    cout << "Aristas procesadas:" << endl;
    MST::Kruskal(matrix,vertexNum, mstKruskal);
    MST::Prim(matrix, vertexNum ,0,mstPrim);
    return 1;
}