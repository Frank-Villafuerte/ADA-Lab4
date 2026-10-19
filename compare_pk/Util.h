#include <vector>
#include "types.h"

class Util
{
	static void EdgesIndex(int vertexNum, std::vector<int>& indexes);
public:
	static void CreateGraph(int vertexNum, int edgeNum, std::vector<Edge>& outEdges);
};