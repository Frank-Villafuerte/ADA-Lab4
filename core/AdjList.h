#pragma once
#include "types.h"
#include <vector>
#include <string>
class AdjList
{
private:
	std::vector<std::vector<Edge>> mList;
	int mVertexNum;
public:
	AdjList(int theVertexNum);
	bool AddEdge(int theVertex1, int theVertex2, int theWeight);
	void GetEdgesByIdx(int vertexIdx, std::vector<Edge>& outputEdgeList);
	void LoadEdges(std::vector<Edge> theEdges);
	void Print();
	void Export(std::string filename);

};