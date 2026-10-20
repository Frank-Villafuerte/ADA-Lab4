#include "AdjMatrix.h"
#include "AdjList.h"
#include <iostream>
#include <algorithm>
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
        outputMatrix.Export("prim_step" + to_string(visitedVertex.size() - 1) + ".txt");
    }
    cout << "Prim: " << processedEdgeCount << " aristas." << endl;
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
        if (forestList[edgeList[i].v].parent != forestList[edgeList[i].w].parent)
        {
            int oldParent = forestList[edgeList[i].w].parent;
            int newParent = forestList[edgeList[i].v].parent;
            for (Forest& f : forestList)
            {
                if (f.parent == oldParent)
                {
                    f.parent = newParent;
                    
                }
                //cout << "{" << f.edge << "," << f.parent << "}" << " ";
            }
            //cout << endl;
            outputMatrix.AddEdge(edgeList[i].v, edgeList[i].w, edgeList[i].weight);
            outputMatrix.Export("kruskal_step" + to_string(processedEdgeCount) + ".txt");
            procCount++;
        }
        else
        {
            //cout << "ciclo" << endl;
        }
    }
    
    cout << "Kruskal: " << processedEdgeCount << " aristas." << endl;
}
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
    {
        cout << "(" << (char)(edge.v + 65) << "," << (char)(edge.w+65) << "," << edge.weight << "),";
    }
    cout << endl;
    matrix.LoadEdges(edges);
    matrix.Export("original.txt");
    cout << "Aristas procesadas:" << endl;
    Kruskal(matrix,vertexNum, mstKruskal);
    Prim(matrix, vertexNum, mstPrim);

    
    
   

    


    return 1;
}