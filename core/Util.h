#pragma once
#include <vector>
#include "types.h"

class Util
{
	static void EdgesIndex(int vertexNum, std::vector<int>& indexes);
public:
	static void CreateRandomGraph(int vertexNum, int edgeNum, std::vector<Edge>& outEdges);
	static int Random(int min, int max);

};