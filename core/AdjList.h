#pragma once
#include "types.h"
#include <vector>
class AdjList
{
private:
	std::vector<std::vector<Edge>> mList;
	int mVertexNum;
public:
	AdjList(int theVertexNum);
	bool AddEdge(int theVertex1, int theVertex2, int theWeight);
	void Print();

};