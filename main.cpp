#include "src/MatrixProduct.cpp"
#include "src/RandomMatrixGenerator.cpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>

int main(int argc, char *argv[])
{
    const size_t N = 10, M = 10, matrixCount = 10000;
    const double sparsity = 0.1;
    
    RandomMatrixGenerator<N,M,bool> generator = RandomMatrixGenerator<N,M,bool>(12123);

    std::vector<Matrix<N,M,bool>> inputMatrices;
    for (size_t i = 0; i < matrixCount; i++) {
        inputMatrices.push_back(generator.generate_generic(sparsity));
    }
        
    std::vector<double> randomVector = Utils::generate_random_vector(M);

    /*
    // Print matrices
    for (auto& inputMatrix : inputMatrices) {
        std::cout << inputMatrix.to_string() << std::endl;
    }
    */

    std::vector<BitsetMatrix<N,M>> bitset_matrices = std::vector<BitsetMatrix<N,M>>(inputMatrices.size());
    std::transform(inputMatrices.begin(), inputMatrices.end(), bitset_matrices.begin(), [](Matrix<N,M,bool> m){return BitsetMatrix<N,M>(m);});

    uint naive_time = Utils::time_exec(
        [&inputMatrices, &randomVector](){
            for (auto& inputMatrix : inputMatrices) {
               MatrixProduct::naive_matrix_vector(inputMatrix, randomVector); 
            }
        }
    );

    uint ps_time = Utils::time_exec(
        [&bitset_matrices, &randomVector](){
            MatrixProduct::ps_matrix_vector(bitset_matrices, randomVector);
        }
    );

    std::cout << "Naive: " << naive_time << " Hashing: " << ps_time << std::endl;
    std::cout << "Speedup: " << static_cast<float>(naive_time)/ps_time << std::endl;

    return 0;
}