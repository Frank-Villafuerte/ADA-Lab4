#include "PriorityQueue.h"
#include <iostream>
using namespace std;
void PriorityQueue::Swap(Edge& edge1, Edge& edge2)
{
	Edge aux = edge1;
	edge1 = edge2;
	edge2 = aux;
}

void PriorityQueue::Enqueue(Edge edge)
{
	edgeHeap.push_back(edge);
	int actualPos = edgeHeap.size()-1;
	SiftUp(actualPos);
}

Edge PriorityQueue::Pop()
{
	Edge output = edgeHeap[0];
	edgeHeap[0] = edgeHeap[edgeHeap.size() - 1];
	edgeHeap.pop_back();
	SiftDown(0);
	return output;
}

bool PriorityQueue::IsEmpty()
{
	return edgeHeap.empty();
}

void PriorityQueue::SiftUp(int actualIdx)
{
	if (actualIdx == 0)
		return;
	if (edgeHeap[(actualIdx - 1) / 2].weight > edgeHeap[actualIdx].weight)
	{
		Swap(edgeHeap[(actualIdx - 1) / 2], edgeHeap[actualIdx]);
		SiftUp((actualIdx - 1) / 2);
	}
}

void PriorityQueue::SiftDown(int actualIdx)
{
	int minIdx = actualIdx;
	if (2 * (actualIdx + 1) - 1 < edgeHeap.size() && edgeHeap[minIdx].weight > edgeHeap[2 * (actualIdx + 1) - 1].weight)
	{
		minIdx = 2 * (actualIdx + 1) - 1;
	}
	if (2 * (actualIdx + 1) < edgeHeap.size() && edgeHeap[minIdx].weight > edgeHeap[2 * (actualIdx + 1)].weight)
	{
		minIdx = 2 * (actualIdx + 1);
	}

	if (minIdx !=actualIdx)
	{
		Swap(edgeHeap[actualIdx], edgeHeap[minIdx]);
		SiftDown(minIdx);
	}
	
}

void PriorityQueue::Print()
{
	for (Edge e : edgeHeap)
		cout << e.weight << " ";
	cout << endl;
}
