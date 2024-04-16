#include "src/MatrixProduct.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath> 

int main(int argc, char *argv[])
{
    
    Matrix<15, 30, bool> m(true);

    std::vector<bool> entries = {true,true,true,true,true,true,true};
    std::vector<size_t> col_index = {1,1,2,2,3,4,3};
    std::vector<size_t> row_index = {0,1,3,6,6,7};
    SparseMatrix<bool> sp_m(entries, col_index, row_index);

    std::cout << sp_m.to_string();

    std::vector<double> input = {0.00032, 1.231, 42, 51232, 0.000000053};

    auto result = MatrixProduct::bin_matrix_vector(sp_m, input);

    return 0;
}