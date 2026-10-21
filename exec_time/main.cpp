#include "AdjMatrix.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "Util.h"
using namespace std;
struct Forest
{
    int edge;
    int parent;
};

void Prim(AdjMatrix inputMatrix,int vertexNum, AdjMatrix& outputMatrix)
{
    vector<int> visitedVertex;
    int startVertex = 0;
    visitedVertex.push_back(startVertex);
    int processedEdgeCount = 0;
    while (visitedVertex.size() < vertexNum)
    {
        int minRIdx = visitedVertex[0];
        int minCIdx = 0;
        for (int i = 0;i < visitedVertex.size();i++)
            for (int j = 0;j < vertexNum;j++)
                if (visitedVertex[i] != j && inputMatrix.GetEdgeWeight(visitedVertex[i], j) != -1)//ignorar diagonal y si la arista evaluada no existe
                {
                    processedEdgeCount++;
                    if (inputMatrix.GetEdgeWeight(minRIdx, minCIdx) == -1 || inputMatrix.GetEdgeWeight(minRIdx, minCIdx) > inputMatrix.GetEdgeWeight(visitedVertex[i], j))
                    {
                        minRIdx = visitedVertex[i];
                        minCIdx = j;
                    }
                }
        outputMatrix.AddEdge(minRIdx, minCIdx, inputMatrix.GetEdgeWeight(minRIdx, minCIdx));
        inputMatrix.EraseCol(minCIdx);
        inputMatrix.EraseEdge(minRIdx, minCIdx);
        visitedVertex.push_back(minCIdx);
    }
    //cout << "Prim: " << processedEdgeCount << " aristas." << endl;
}
int Find(int node,vector<Forest>& forestList)
{
    if (forestList[node].edge == forestList[node].parent)
    {
        return node;
    }
    forestList[node].parent = Find(forestList[node].parent, forestList);
    return forestList[node].parent;
}
void Kruskal(AdjMatrix inputMatrix, int vertexNum, AdjMatrix& outputMatrix)
{
    vector<Edge> edgeList;
    vector<Forest> forestList;
    int processedEdgeCount=0;
    for(int i=0;i<vertexNum;i++)
        for (int j = 0;j < i;j++)
        {
            int weight = inputMatrix.GetEdgeWeight(i,j);
            if (weight != -1)
                edgeList.push_back({i,j,weight});
        }
    sort(edgeList.begin(),edgeList.end(), [](Edge edge1, Edge edge2) {
        return edge1.weight < edge2.weight;
        });//ordenar
    
    for (int i = 0;i < vertexNum;i++)
    {
        forestList.push_back({i,i});
    }
    int procCount = 0;
    for (int i = 0;i < edgeList.size()&&procCount<vertexNum-1;i++)
    {
        processedEdgeCount++;
        int parentV = Find(edgeList[i].v,forestList);
        int parentW = Find(edgeList[i].w, forestList);
        //if (forestList[edgeList[i].v].parent != forestList[edgeList[i].w].parent)
        if(parentV!=parentW)
        {
            forestList[parentW].parent = parentV;
            outputMatrix.AddEdge(edgeList[i].v, edgeList[i].w, edgeList[i].weight);
            procCount++;
        }
        else
        {
            //cout << "ciclo" << endl;
        }
    }
    
    //cout << "Kruskal: " << processedEdgeCount << " aristas." << endl;
}
int main()
{
    vector<int> testValues = {10,50,100};
    for (int value : testValues)
    {
        int vertexNum = value;
        int edgeNum = Util::Random(value,value*value);
        cout << "Vertices: " << vertexNum << endl;
        cout << "Aristas: " << edgeNum << endl;
        AdjMatrix matrix(vertexNum);
        AdjMatrix mstPrim(vertexNum);
        AdjMatrix mstKruskal(vertexNum);
        vector<Edge> edges;
        Util::CreateRandomGraph(vertexNum, edgeNum, edges);
        matrix.LoadEdges(edges);
        matrix.Export("original_"+to_string(value) + ".txt");
        auto start = std::chrono::steady_clock::now();
        Kruskal(matrix, vertexNum, mstKruskal);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::nano> duration = end-start;
        cout << "Kruskal: " << duration.count() / 1000000 << "ms" << endl;
        start = std::chrono::steady_clock::now();
        Prim(matrix, vertexNum, mstPrim);
        end = std::chrono::steady_clock::now();
        duration = end - start;
        cout << "Prim: " << duration.count()/1000000<<"ms" << endl;
        mstKruskal.Export("kruskal_" + to_string(value) + ".txt");
        mstPrim.Export("prim_" + to_string(value) + ".txt");
        cout << "===========================================" << endl;
    }
    return 1;
}