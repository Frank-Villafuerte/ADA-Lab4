#include "AdjMatrix.h"
#include "AdjList.h"
#include <iostream>
#include <algorithm>
#include "Util.h"
#include "MST.h"
#include "PriorityQueue.h"
using namespace std;
void Prim(AdjMatrix inputMatrix, int vertexNum, int startVertex, AdjMatrix& outputMatrix)
{
    //int startVertex = 0;
    vector<bool> visitedVertex(vertexNum, false);
    visitedVertex[startVertex] = true;
    vector<int> minWeightIdx(vertexNum,startVertex);
    for (int i = 0; i < vertexNum; i++) {

        minWeightIdx[i] = startVertex;
    }
    int connectedVertex = 1;
    while (connectedVertex < vertexNum)
    {
        int minTargetIdx = -1;//columna de menor peso
        int lowerWeight = -1;
        for (int j = 0; j < vertexNum; j++) {
            int evalWeight = inputMatrix.GetEdgeWeight(minWeightIdx[j], j);
            if (!visitedVertex[j] && evalWeight != -1) {
                if (lowerWeight == -1 || evalWeight < lowerWeight) {
                    lowerWeight = evalWeight;
                    minTargetIdx = j;
                }
            }
        }
        if (minTargetIdx == -1) { cout << "Grafo disconexo";break; }
        visitedVertex[minTargetIdx] = true;
        outputMatrix.AddEdge(minWeightIdx[minTargetIdx], minTargetIdx, inputMatrix.GetEdgeWeight(minWeightIdx[minTargetIdx], minTargetIdx));
        connectedVertex++;
        for (int i = 0;i < vertexNum;i++)
        {
            int actualMinWeight = inputMatrix.GetEdgeWeight(minWeightIdx[i], i);
            int evalMinWeight = inputMatrix.GetEdgeWeight(minTargetIdx, i);
            if (evalMinWeight!=-1 )
                if(actualMinWeight==-1||evalMinWeight<actualMinWeight)
                    minWeightIdx[i] = minTargetIdx;
        }
    }
}
void Prim(AdjList inputList, int vertexNum, int startVertex, AdjList& outputList)
{
    vector<bool> visitedVertex(vertexNum, false);
    visitedVertex[startVertex] = true;
    vector<int> minWeight(vertexNum, -1);
    vector<int> minVertex(vertexNum,-1);
 
    vector<Edge> edgeList;
    inputList.GetEdgesByIdx(startVertex, edgeList);
    for (Edge e: edgeList) {
        minWeight[e.w] = e.weight;
        minVertex[e.w] = startVertex;
    }
    int connectedVertex = 1;
    while (connectedVertex < vertexNum)
    {
        int minTargetIdx = -1;//columna de menor peso
        int lowerWeight = -1;
        for (int j = 0; j < vertexNum; j++) {
            int evalWeight = minWeight[j];
            if (!visitedVertex[j] && evalWeight != -1) {
                if (lowerWeight == -1 || evalWeight < lowerWeight) {
                    lowerWeight = evalWeight;
                    minTargetIdx = j;
                }
            }
        }
        if (minTargetIdx == -1) { cout << "Grafo disconexo";break; }
        visitedVertex[minTargetIdx] = true;
        outputList.AddEdge(minVertex[minTargetIdx], minTargetIdx, lowerWeight);
        connectedVertex++;
        inputList.GetEdgesByIdx(minTargetIdx, edgeList);
        for (Edge e : edgeList)
        {
            if (!visitedVertex[e.w]&&(minWeight[e.w]==-1||e.weight<minWeight[e.w]))
            {
                minWeight[e.w] = e.weight;
                minVertex[e.w] = e.v;
            }
        }
    }
}
int main()
{
    //(A,D,5), (C,E,5), (D,F,6), (A,B,7), (B,E,7), (B,C,8), (E,F,8), (B,D,9), (E,G,9), (F,G,11), (D,E,15)
    //(A,D,5) (C,E,5) (D,F,6) (A,B,7) (B,E,7) (B,C,8) (E,F,8) (B,D,9) (E,G,9) (F,G,1) (D,E,1)
    //A,B,C,D,E,F,G
    //0,1,2,3,4,5,6
    //PriorityQueue queue;
    vector<Edge> edges = { {0,3,5},{2,4,5},{3,5,6}, {0,1,7}, {1,4,7}, {1,2,8}, {4,5,8}, {1,3,9}, {4,6,9}, {5,6,11}, {3,4,15} };
    vector<Edge> edgesUnco = { {0,3,5},{2,4,5}, {0,1,7}, {1,4,7}, {1,2,8}, {1,3,9}, {5,6,11}, {3,4,15} };//disconexo
    int vertexNum;
    int edgeNum;
    /*AdjList list(7);
    AdjList mst(7);
    list.LoadEdges(edges);
    Prim(list,7,0,mst);
    list.Print();
    cout << endl;
    mst.Print();*/
    AdjMatrix matrix(7);
    AdjMatrix mst(7);
    matrix.LoadEdges(edgesUnco);
    matrix.Export("matrix.txt");
    matrix.Print();
    //Prim(matrix,7,0,mst);
    MST::Prim(matrix, 7, 0, mst);
    mst.Export("mstprim.txt");
    cout << endl;
    
    return 1;
}