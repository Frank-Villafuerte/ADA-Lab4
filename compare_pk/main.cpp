#include "AdjMatrix.h"

int main()
{
    AdjMatrix matrix(10);

    matrix.AddEdge(2,5,8);
    matrix.AddEdge(5, 10, 4);
    matrix.Print();
    
    return 1;
}