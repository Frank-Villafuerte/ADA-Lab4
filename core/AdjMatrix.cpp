#include "AdjMatrix.h"
#include <iostream>
#include <fstream>

using namespace std;

AdjMatrix::AdjMatrix(int theVertexNum)
{
    mVertexNum = theVertexNum;
    
    vector<int> row;
    row.resize(theVertexNum,-1);
    mMatrix.resize(theVertexNum, row);
}
int AdjMatrix::GetEdgeWeight(int theVertex1, int theVertex2)
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

void AdjMatrix::EraseEdge(int theVertex1, int theVertex2)
{
    mMatrix[theVertex1][theVertex2] = -1;
    mMatrix[theVertex2][theVertex1] = -1;
}

void AdjMatrix::EraseCol(int theCol)
{
    for (int i = 0;i < mVertexNum;i++)
    {
        mMatrix[i][theCol] = -1;
    }
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

void AdjMatrix::LoadEdges(std::vector<Edge> theEdges)
{
    for (int i = 0;i < theEdges.size();i++)
    {
        AddEdge(theEdges[i].v, theEdges[i].w, theEdges[i].weight);
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

void AdjMatrix::Export(string theFilename)
{
    ofstream file(theFilename);
    vector<string> lines;
    lines.push_back(to_string(mVertexNum)+" ");
    int edgeCount=0;
    for (int i = 0;i < mVertexNum;i++)
        for (int j = 0;j < i;j++)
        {
            int weight = mMatrix[i][j];
            if (weight != -1)
            {
                if(mVertexNum<27)
                    lines.push_back ( string(1,(char)(i + 65)) + " " +string(1,(char)(j + 65)) +" "+to_string(weight)+"\n");
                else
                    lines.push_back(to_string(i) + " " + to_string(j) + " " + to_string(weight) + "\n");
                edgeCount++;
            }
        }
    lines[0] += to_string(edgeCount)+"\n";
    if (file.is_open()) {

        for (string line : lines)
            file << line;

        file.close();
        //cout << "Archivo escrito correctamente:" <<theFilename<< endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

