#pragma once
#include "AdjMatrix.h"
#include "AdjList.h"
#include "types.h"
#include <vector>
class MST
{
private:
	static int Find(int node, std::vector<Forest>& forestList);
public:
	static void Prim(AdjMatrix inputMatrix, int vertexNum, int startVertexIdx, AdjMatrix& outputMatrix);
	static void Prim(AdjList inputList, int vertexNum, int startVertexIdx, AdjList& outputList);
	static void Kruskal(AdjMatrix inputMatrix, int vertexNum, AdjMatrix& outputMatrix);
	static void Kruskal(AdjList inputList, int vertexNum, AdjList& outputList);
};