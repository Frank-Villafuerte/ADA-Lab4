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

void AdjMatrix::Print()
{
    for (int i = 0;i < mVertexNum * mVertexNum;i++)
    {
        if (i % mVertexNum == 0)
        {
            cout << endl;
        }
        cout << mMatrix.at(i);
    }
}

