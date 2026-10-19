#include <vector>

//Matriz cuenta los vértices desde 0
class AdjMatrix
{
private:
    std::vector<std::vector<int>> mMatrix;
    int mVertexNum;
public:
    AdjMatrix(int theVertexNum);
    int GetEdge(int col, int row);
    bool AddEdge(int theVertex1, int theVertex2, int theWeight);
    void GetUnconnectedIdx(std::vector<int>& theOutUnconnected);
    void Print();
    void Export();
};
