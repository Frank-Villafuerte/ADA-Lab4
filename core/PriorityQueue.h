#pragma once
#include <vector>
#include "types.h"
class PriorityQueue
{
private:
	std::vector<Edge> edgeHeap;

	void Swap(Edge& edge1, Edge& edge2);
	void SiftUp(int actualIdx);
	void SiftDown(int actualIdx);
public:
	void Enqueue(Edge edge);	
	Edge Pop();
	bool IsEmpty();
	void Print();
};