#include "src/MatrixProduct.cpp"
#include "src/datastructs/SparseBoolMatrix.cpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
    
    Matrix<15, 30, bool> m(true);

    std::vector<size_t> col_index = {1,1,2,2,3,4,3};
    std::vector<size_t> row_index = {0,1,3,6,6,7};

    SparseBoolMatrix sbm(col_index, row_index);

    std::cout << m.to_string() << std::endl;

    std::cout << sbm.to_string();

    std::vector<double> input = {0.00032, 1.231, 42, 51232, 0.000000053};

    std::vector<double> result;
    uint time = Utils::time_exec(
        [&result, &input, &sbm](){result = MatrixProduct::bin_matrix_vector(sbm, input);}
    );
     
    std::cout << "Result: " << Utils::vec_to_str<double>(result) << std::endl;
    std::cout << "Time: " << time << "ns" << std::endl;

    return 0;
}