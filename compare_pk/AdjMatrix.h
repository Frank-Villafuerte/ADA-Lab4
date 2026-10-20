#pragma once
#include <vector>
#include <string>
#include "types.h"

//Matriz cuenta los vértices desde 0
class AdjMatrix
{
private:
    std::vector<std::vector<int>> mMatrix;
    int mVertexNum;
public:
    AdjMatrix(int theVertexNum);
    int GetEdgeWeight(int theVertex1, int theVertex2);
    bool AddEdge(int theVertex1, int theVertex2, int theWeight);
    void EraseEdge(int theVertex1, int theVertex2);
    void EraseCol(int theCol);
    void GetUnconnectedIdx(std::vector<int>& theOutUnconnected);
    void LoadEdges(std::vector<Edge> theEdges);
    void Print();
    void Export(std::string theFilename);
};
