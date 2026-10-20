#pragma once
#include <vector>
#include "types.h"

class Util
{
	static void EdgesIndex(int vertexNum, std::vector<int>& indexes);
public:
	static void CreateRandomGraph(int vertexNum, int edgeNum, std::vector<Edge>& outEdges);
	static int Min(int num1, int num2);

};