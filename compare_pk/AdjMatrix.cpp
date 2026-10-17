#include "AdjMatrix.h"
#include <iostream>
using namespace std;

AdjMatrix::AdjMatrix(int theVertexNum)
{
    mVertexNum = theVertexNum;
    mMatrix.resize(theVertexNum*theVertexNum,-1);
}
int AdjMatrix::GetElement(int col, int row)
{
    if (row * mVertexNum + col < mMatrix.size())
    {
        return -1;
    }
    return mMatrix.at(mVertexNum * row + col);
}

bool AdjMatrix::AddEdge(int theVertex1, int theVertex2, int theWeight)
{
    if (theVertex1 >= mVertexNum || theVertex2 >= mVertexNum)
    {
        cout << "[ERR] AdjMatrix.AddEdge: Fuera de rango" << endl;
        return false;
    }
    if (mMatrix[theVertex1 * mVertexNum + theVertex2] != -1)
    {
        cout << "[ERR] AdjMatrix.AddEdge: Arista ya existe" << endl;
        return false;
    }
    mMatrix[theVertex1 * mVertexNum + theVertex2] = theWeight;
    mMatrix[theVertex2 * mVertexNum + theVertex1] = theWeight;
    return true;
}

void AdjMatrix::Print()
{
    for (int i = 0;i < mVertexNum * mVertexNum;i++)
    {
        if (i % mVertexNum == 0)
        {
            cout << endl;
        }
        cout << mMatrix.at(i)<<" ";
    }
}

