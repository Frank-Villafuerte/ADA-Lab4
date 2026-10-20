#pragma once
struct Edge
{
	int v;
	int w;
	int weight;

	bool operator==(Edge other)
	{
		return v == other.v && w == other.w;
	}
};