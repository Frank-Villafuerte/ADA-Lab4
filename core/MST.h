#pragma once
#include "AdjMatrix.h"
#include "types.h"
#include <vector>
class MST
{
private:
	static int Find(int node, std::vector<Forest>& forestList);
public:
	static void Prim(AdjMatrix inputMatrix, int vertexNum, int startVertexIdx, AdjMatrix& outputMatrix);
	
	static void Kruskal(AdjMatrix inputMatrix, int vertexNum, AdjMatrix& outputMatrix);
};