#include <vector>

//Matriz cuenta los vértices desde 0
class AdjMatrix
{
private:
    std::vector<int> mMatrix;
    int mVertexNum;
public:
    AdjMatrix(int theVertexNum);
    int GetElement(int col, int row);
    bool AddEdge(int theVertex1, int theVertex2, int theWeight);
    void Print();
};
