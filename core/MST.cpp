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
    for (int j = 0;j < vertexNum;j++)
        if(!visitedVertex[j]&&inputMatrix.GetEdgeWeight(startVertexIdx,j)!=-1)
            queue.Enqueue({startVertexIdx,j,inputMatrix.GetEdgeWeight(startVertexIdx,j) });
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
        outputMatrix.AddEdge(lowest.v, lowest.w, lowest.weight);
        connectedVertex++;
        for (int j = 0;j < vertexNum;j++)
            if (!visitedVertex[j] && inputMatrix.GetEdgeWeight(lowest.w, j) != -1)
                queue.Enqueue({ lowest.w,j ,inputMatrix.GetEdgeWeight(lowest.w, j) });
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