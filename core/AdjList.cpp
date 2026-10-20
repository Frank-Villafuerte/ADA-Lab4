#include "AdjList.h"
#include <algorithm>
#include <iostream>
using namespace std;
AdjList::AdjList(int theVertexNum)
{
    mVertexNum = theVertexNum;
    vector<Edge> vertexConn;
    mList.resize(theVertexNum, vertexConn);//iniciar vectores vacios
}

bool AdjList::AddEdge(int theVertex1, int theVertex2, int theWeight)
{
    if (theVertex1 == theVertex2)
    {
        cout << "[ERR] AdjList.AddEdge: Vértice autoconectado" << endl;
        return false;
    }
    if (theVertex1 >= mVertexNum || theVertex2 >= mVertexNum)
    {
        cout << "[ERR] AdjList.AddEdge: Fuera de rango" << endl;
        return false;
    }
    Edge newEdge = { theVertex1,theVertex2,theWeight };
    if (find(mList[theVertex1].begin(), mList[theVertex1].end(),newEdge )!=mList[theVertex1].end())
    {
        cout << "[ERR] AdjList.AddEdge: Arista ya existe" << endl;
        return false;
    }
    mList[theVertex1].push_back({theVertex1,theVertex2,theWeight});
    mList[theVertex2].push_back({ theVertex2,theVertex1,theWeight });
    //agregar ambos al ser no dirigidos
    
    return true;
}

void AdjList::Print()
{
    for (int i = 0;i < mList.size();i++)
    {
        cout << "["<<(char)(i + 65)<<"] ";
        for (Edge e : mList[i])
        {
            cout << "(" << (char)(e.w+65) <<"," << e.weight << ")";
        }
        cout << endl;
    }
}
