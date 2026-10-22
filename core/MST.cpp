#include "MST.h"
#include "PriorityQueue.h"
#include <iostream>
#include <algorithm>
using namespace std;

void MST::Prim(AdjMatrix inputMatrix, int vertexNum, int startVertexIdx, AdjMatrix& outputMatrix)
{
    PriorityQueue queue;
    vector<bool> visitedVertex(vertexNum, false);
    visitedVertex[startVertexIdx] = true;
    vector<int> minWeightIdx(vertexNum, startVertexIdx);
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
            if(!visitedVertex[i])
            {
                int actualMinWeight = inputMatrix.GetEdgeWeight(minWeightIdx[i], i);
                int evalMinWeight = inputMatrix.GetEdgeWeight(minTargetIdx, i);
                if (evalMinWeight != -1)
                    if (actualMinWeight == -1 || evalMinWeight < actualMinWeight)
                        minWeightIdx[i] = minTargetIdx;
            }
        }
    }
}
int MST::Find(int node, vector<Forest>& forestList)
{
    if (forestList[node].edge == forestList[node].parent)
    {
        return node;
    }
    forestList[node].parent = Find(forestList[node].parent, forestList);
    return forestList[node].parent;
}
void MST::Kruskal(AdjMatrix inputMatrix, int vertexNum, AdjMatrix& outputMatrix)
{
    vector<Edge> edgeList;
    vector<Forest> forestList;
    int processedEdgeCount = 0;
    for (int i = 0;i < vertexNum;i++)
        for (int j = 0;j < i;j++)
        {
            int weight = inputMatrix.GetEdgeWeight(i, j);
            if (weight != -1)
                edgeList.push_back({ i,j,weight });
        }
    sort(edgeList.begin(), edgeList.end(), [](Edge edge1, Edge edge2) {
        return edge1.weight < edge2.weight;
        });//ordenar por pesos

    for (int i = 0;i < vertexNum;i++)
    {
        forestList.push_back({ i,i });
    }
    int procCount = 0;
    for (int i = 0;i < edgeList.size() && procCount < vertexNum - 1;i++)
    {
        processedEdgeCount++;
        int parentV = Find(edgeList[i].v, forestList);
        int parentW = Find(edgeList[i].w, forestList);
        if (parentV != parentW)
        {
            forestList[parentW].parent = parentV;
            outputMatrix.AddEdge(edgeList[i].v, edgeList[i].w, edgeList[i].weight);
            outputMatrix.Export("kruskal_step" + to_string(procCount + 1) + ".txt");
            procCount++;
        }
        else
        {
            //cout << "ciclo" << endl;
        }
    }
    cout << "Kruskal: " << processedEdgeCount << " aristas." << endl;
}