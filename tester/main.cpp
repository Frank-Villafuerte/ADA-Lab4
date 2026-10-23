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
void Prim(AdjList inputList, int vertexNum, int startVertexIdx, AdjList& outputList)
{
    PriorityQueue queue;
    vector<bool> visitedVertex(vertexNum, false);
    visitedVertex[startVertexIdx] = true;
    vector<Edge> edgeList;
    inputList.GetEdgesByIdx(startVertexIdx, edgeList);
    for (Edge e : edgeList) {
        if (!visitedVertex[e.w])
            queue.Enqueue(e);
    }
    queue.Print();
    int connectedVertex = 1;
    while (connectedVertex < vertexNum)
    {
        Edge lowest;
        do
        {
            if (queue.IsEmpty())
            {
                cout << "Grafo no conexo" << endl;
                return;
            }
            lowest = queue.Pop();
            queue.Print();
        } while (visitedVertex[lowest.w]);
        visitedVertex[lowest.w] = true;
        outputList.AddEdge(lowest.v, lowest.w, lowest.weight);
        connectedVertex++;
        inputList.GetEdgesByIdx(lowest.w, edgeList);
        for (Edge e : edgeList) {
            if (!visitedVertex[e.w])
                queue.Enqueue(e);
        }
    }/*
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
    }*/
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
    AdjList list(7);
    AdjList mstPrim(7);
    AdjList mstKruskal(7);
    list.LoadEdges(edges);
    MST::Prim(list, 7, 0, mstPrim);
    MST::Kruskal(list, 7, mstKruskal);
    mstPrim.Export("mstprim.txt");
    mstKruskal.Export("mstkruskal.txt");

    
    /*AdjMatrix matrix(7);
    AdjMatrix mstPrim(7);
    AdjMatrix mstKruskal(7);
    matrix.LoadEdges(edges);
    matrix.Export("matrix.txt");
    matrix.Print();
    //Prim(matrix,7,0,mst);
    MST::Prim(matrix, 7, 0, mstPrim);
    MST::Kruskal(matrix, 7, mstKruskal);
    mstPrim.Export("mstprim.txt");
    mstKruskal.Export("mstkruskal.txt");
    cout << endl;
    */
    return 1;
}