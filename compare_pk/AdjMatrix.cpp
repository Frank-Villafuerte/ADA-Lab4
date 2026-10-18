#include "AdjMatrix.h"
#include <iostream>
using namespace std;

AdjMatrix::AdjMatrix(int theVertexNum)
{
    mVertexNum = theVertexNum;
    
    vector<int> row;
    row.resize(theVertexNum,-1);
    mMatrix.resize(theVertexNum, row);
}
int AdjMatrix::GetEdge(int theVertex1, int theVertex2)
{
    if (theVertex1 >= mVertexNum || theVertex2 >= mVertexNum)
    {
        cout << "[ERR] AdjMatrix.GetEdge: Fuera de rango" << endl;
        return -1;
    }
    return mMatrix[theVertex1][theVertex2];
}

bool AdjMatrix::AddEdge(int theVertex1, int theVertex2, int theWeight)
{
    if (theVertex1 == theVertex2)
    {
        cout << "[ERR] AdjMatrix.AddEdge: Vértice autoconectado" << endl;
        return false;
    }
    if (theVertex1 >= mVertexNum || theVertex2 >= mVertexNum)
    {
        cout << "[ERR] AdjMatrix.AddEdge: Fuera de rango" << endl;
        return false;
    }
    if (mMatrix[theVertex1][theVertex2] != -1)
    {
        cout << "[ERR] AdjMatrix.AddEdge: Arista ya existe" << endl;
        return false;
    }
    //agregar ambos al ser no dirigidos
    mMatrix[theVertex1][theVertex2] = theWeight;
    mMatrix[theVertex2][theVertex1] = theWeight;
    return true;
}

void AdjMatrix::Print()
{
    for (int i = 0;i < mVertexNum;i++)
    {
        for (int j = 0;j < mVertexNum;j++)
        {
            cout << mMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

