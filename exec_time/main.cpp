#include "MST.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "Util.h"
using namespace std;
int main()
{
    vector<int> testValues = {10,50,100};
    for (int value : testValues)
    {
        int vertexNum = value;
        int edgeNum = Util::Random(value,value*value);
        cout << "Vertices: " << vertexNum << endl;
        cout << "Aristas: " << edgeNum << endl;
        AdjList graph(vertexNum);
        AdjList mstPrim(vertexNum);
        AdjList mstKruskal(vertexNum);
        vector<Edge> edges;
        Util::CreateRandomGraph(vertexNum, edgeNum, edges);
        graph.LoadEdges(edges);
        graph.Export("original_"+to_string(value) + ".txt");
        auto start = std::chrono::steady_clock::now();
        MST::Kruskal(graph, vertexNum, mstKruskal);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::nano> duration = end-start;
        cout << "Kruskal: " << duration.count() / 1000000 << "ms" << endl;
        start = std::chrono::steady_clock::now();
        MST::Prim(graph, vertexNum,0, mstPrim);
        end = std::chrono::steady_clock::now();
        duration = end - start;
        cout << "Prim: " << duration.count()/1000000<<"ms" << endl;
        mstKruskal.Export("kruskal_" + to_string(value) + ".txt");
        mstPrim.Export("prim_" + to_string(value) + ".txt");
        cout << "===========================================" << endl;
    }
    return 1;
}