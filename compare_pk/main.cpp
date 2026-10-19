#include "AdjMatrix.h"
#include <iostream>
#include "Util.h"
using namespace std;
int main()
{
    //AdjMatrix matrix(10);

    //matrix.AddEdge(2,5,8);
    //matrix.AddEdge(5, 10, 4);
    //matrix.Print();
    //cout<<matrix.GetEdge(5, 2)<<endl;
    vector<Edge> edges;
    Util::CreateGraph(5, 10,edges);
    return 1;
}