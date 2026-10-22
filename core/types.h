#pragma once
#include <string>
struct Edge
{
	int v;
	int w;
	int weight;

	bool operator==(Edge other)
	{
		return v == other.v && w == other.w||v==other.w&&w==other.v;
	}
};
struct Forest
{
	int edge;
	int parent;
};