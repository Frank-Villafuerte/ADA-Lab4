#include "MST.h"
#include "Util.h"
#include <iostream>
#include <chrono>
using namespace std;
int main()
{
    vector<float> testValues = { 0.3,0.5,0.8 };//densidad
    for (float value : testValues)
    {
        int vertexNum = 200;
        int edgeNum = vertexNum*vertexNum*value;
        cout << "Vertices: " << vertexNum << endl;
        cout << "Aristas: " << edgeNum << endl;
        AdjList graphList(vertexNum);
        AdjList mstPrimL(vertexNum);
        AdjList mstKruskalL(vertexNum);
        AdjMatrix graphMatrix(vertexNum);
        AdjMatrix mstPrimM(vertexNum);
        AdjMatrix mstKruskalM(vertexNum);
        vector<Edge> edges;
        Util::CreateRandomGraph(vertexNum, edgeNum, edges);
        graphList.LoadEdges(edges);
        graphMatrix.LoadEdges(edges);
        cout << "---------------------------------" << endl;
        auto start = std::chrono::steady_clock::now();
        MST::Kruskal(graphList, vertexNum, mstKruskalL);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::nano> duration = end - start;
        cout << "Kruskal List: " << duration.count() / 1000000 << "ms" << endl;
        start = std::chrono::steady_clock::now();
        MST::Prim(graphList, vertexNum, 0, mstPrimL);
        end = std::chrono::steady_clock::now();
        duration = end - start;
        cout << "Prim List: " << duration.count() / 1000000 << "ms" << endl;
        start = std::chrono::steady_clock::now();
        MST::Kruskal(graphMatrix, vertexNum, mstKruskalM);
        end = std::chrono::steady_clock::now();
        duration = end - start;
        cout << "Kruskal Matrix: " << duration.count() / 1000000 << "ms" << endl;
        start = std::chrono::steady_clock::now();
        MST::Prim(graphMatrix, vertexNum, 0, mstPrimM);
        end = std::chrono::steady_clock::now();
        duration = end - start;
        cout << "Prim Matrix: " << duration.count() / 1000000 << "ms" << endl;
        mstKruskalL.Export("kruskalList_" + to_string(value).substr(0, 4) + ".txt");
        mstPrimL.Export("primList_" + to_string(value).substr(0, 4) + ".txt");
        mstKruskalM.Export("kruskalMatrix_" + to_string(value).substr(0,4) + ".txt");
        mstPrimM.Export("primMatrix_" + to_string(value).substr(0, 4) + ".txt");
        cout << "===========================================" << endl;
    }
    return 1;
}