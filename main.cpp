#include "src/SparseMatrix.cpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath> 

int main(int argc, char *argv[])
{
    
    Matrix<15, 30, bool> m(true);

    std::vector<int> entries = {1,3,5};
    std::vector<size_t> col_index = {1,1,2};
    std::vector<size_t> row_index = {0,1,2,3};

    SparseMatrix<int> sp_m(entries, col_index, row_index);

    std::cout << sp_m.to_string();

    return 0;
}