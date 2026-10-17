#include <vector>

class AdjMatrix
{
private:
    std::vector<int> mMatrix;
    int mVertexNum;
public:
    AdjMatrix(int theVertexNum);
    int GetElement(int col, int row);
    void Print();
};
