#include "AdjMatrix.h"
#include <iostream>
#include <fstream>
#include <string>
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

void AdjMatrix::GetUnconnectedIdx(std::vector<int>& theOutUnconnected)
{
    theOutUnconnected.clear();
    for(int i=0;i<mVertexNum;i++)
        for (int j = 0;j < i;j++)
        {
            if (i != j && mMatrix[i][j] == -1)
            {
                theOutUnconnected.push_back(i*mVertexNum+j);
            }
        }
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

void AdjMatrix::Export()
{
    ofstream file("graph.txt");
    vector<string> lines;
    lines.push_back(to_string(mVertexNum)+" ");
    int edgeCount=0;
    for (int i = 0;i < mVertexNum;i++)
        for (int j = 0;j < i;j++)
        {
            int weight = mMatrix[i][j];
            if (weight != -1)
            {
                lines.push_back ( string(1,(char)(i + 65)) + " " +string(1,(char)(j + 65)) +" "+to_string(weight)+"\n");
                edgeCount++;
            }
        }
    lines[0] += to_string(edgeCount)+"\n";
    if (file.is_open()) {

        for (string line : lines)
            file << line;

        file.close();
        cout << "Archivo escrito correctamente." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

