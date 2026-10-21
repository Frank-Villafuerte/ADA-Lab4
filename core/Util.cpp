#include "Util.h"
#include <algorithm>
#include <iostream>

#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include "AdjMatrix.h"
using namespace std;

void Util::EdgesIndex(int vertexNum,vector<int>& indexes)
{
	indexes.clear();
	for (int i = 0;i < vertexNum;i++)
	{
		for (int j = 0;j < vertexNum;j++)
			if(i!=j)
				indexes.push_back(i*vertexNum+j);
	}
}
void Util::CreateRandomGraph(int vertexNum, int edgeNum, vector<Edge>& outEdges)
{
	if (edgeNum < vertexNum)
	{
		cout << "[ERR] Util.creategraph: No hay suficientes aristes para un grafo conexo";
		return;
	}
	vector<int> list;//lista de vertices
	for (int i = 0;i < vertexNum;i++)
	{
		list.push_back(i);
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(list.begin(),list.end(), std::default_random_engine(seed));
	AdjMatrix tempMatrix(vertexNum);//matriz temporal para validar aristas
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<> distrW(1,50);
	uniform_int_distribution<> distrE(0, vertexNum-1);
	
	for (int i = 0;i < list.size();i++)
		tempMatrix.AddEdge(list[i], list[(i + 1) % list.size()], distrW(generator));

	vector<int> unconnectedIdx;
	tempMatrix.GetUnconnectedIdx(unconnectedIdx);
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(unconnectedIdx.begin(), unconnectedIdx.end(), std::default_random_engine(seed));
	//tempMatrix.Print();
	for (int i = 0;i < edgeNum-list.size()&&i<unconnectedIdx.size();i++)
	{
		
		//cout << unconnectedIdx[i] << " " << unconnectedIdx[i] / vertexNum << " " << unconnectedIdx[i] % vertexNum << endl;
		tempMatrix.AddEdge(unconnectedIdx[i] / vertexNum, unconnectedIdx[i] % vertexNum, distrW(generator));
		
	}
	for (int i = 0;i < vertexNum;i++)
	{
		for (int j = 0;j < i;j++)
		{
			int weight = tempMatrix.GetEdgeWeight(i, j);
			if (weight != -1)
				outEdges.push_back({i,j,weight});
		}
	}
	//tempMatrix.Export();
	
}

int Util::Random(int min, int max)
{
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<> distr(min, max);
	return distr(generator);
}
