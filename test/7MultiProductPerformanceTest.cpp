#include <gtest/gtest.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <sstream>
#include <algorithm>

#include "../src/RandomMatrixGenerator.cpp"
#include "../src/MatrixType.cpp"
#include "../src/MatrixProduct.cpp"

class MultiProductPerformanceTests :
        public ::testing::TestWithParam<size_t>{
protected:
    static constexpr size_t N = 100;
    static constexpr size_t M = 100;
    static const int seed = 0;
    
    const double sparsity = 0.05;
};

TEST_P(MultiProductPerformanceTests, MultiProductPerformanceTest) {
    
    size_t matrixCount = GetParam();

    RandomMatrixGenerator<N,M,bool> generator = RandomMatrixGenerator<N,M,bool>(seed);

    std::vector<Matrix<N,M,bool>> inputMatrices;
    for (size_t i = 0; i < matrixCount; i++) {
        inputMatrices.push_back(generator.generate_generic(sparsity));
    }
        
    std::vector<double> randomVector = Utils::generate_random_vector(M);

    uint naive_time = Utils::time_exec(
        [&inputMatrices, &randomVector](){
            for (auto& inputMatrix : inputMatrices) {
               MatrixProduct::naive_matrix_vector(inputMatrix, randomVector); 
            }
        }
    );

    std::vector<SparseBoolMatrix> sparse_bool_matrices = std::vector<SparseBoolMatrix>(inputMatrices.size());
    std::transform(inputMatrices.begin(), inputMatrices.end(), sparse_bool_matrices.begin(), [](Matrix<N,M,bool> m){return SparseBoolMatrix(m);});

    uint opt_time = Utils::time_exec(
        [&sparse_bool_matrices, &randomVector](){
            for (auto& inputMatrix : sparse_bool_matrices) {
               MatrixProduct::bin_matrix_vector(inputMatrix, randomVector); 
            }
        }
    );

    std::vector<RawBoolMatrix<N,M>> raw_bool_matrices = std::vector<RawBoolMatrix<N,M>>(inputMatrices.size());
    std::transform(inputMatrices.begin(), inputMatrices.end(), raw_bool_matrices.begin(), [](Matrix<N,M,bool> m){return RawBoolMatrix<N,M>(m);});

    uint blas_time = Utils::time_exec(
        [&raw_bool_matrices, &randomVector](){
            for (auto& inputMatrix : raw_bool_matrices) {
               MatrixProduct::blas_matrix_vector(inputMatrix, randomVector); 
            }
        }
    );

    std::vector<BitsetMatrix<N,M>> bitset_matrices = std::vector<BitsetMatrix<N,M>>(inputMatrices.size());
    std::transform(inputMatrices.begin(), inputMatrices.end(), bitset_matrices.begin(), [](Matrix<N,M,bool> m){return BitsetMatrix<N,M>(m);});

    uint ps_time = Utils::time_exec(
        [&bitset_matrices, &randomVector](){
            MatrixProduct::ps_matrix_vector(bitset_matrices, randomVector);
        }
    );

    std::stringstream ss;
    ss << matrixCount << "," << naive_time << "," << blas_time << "," << opt_time << "," << ps_time << ','
        << Utils::round_to_n_digits(static_cast<double>(naive_time)/naive_time) << "," 
        << Utils::round_to_n_digits(static_cast<double>(naive_time)/opt_time) << "," 
        << Utils::round_to_n_digits(static_cast<double>(naive_time)/blas_time) << "," 
        << Utils::round_to_n_digits(static_cast<double>(naive_time)/ps_time);

    Utils::create_multi_prod_perf_test_header_if_not_exists();
    Utils::append_to_file("multi_product_performance_results.csv", ss.str());
}

INSTANTIATE_TEST_SUITE_P(
    MultiProductPerformanceTests,
    MultiProductPerformanceTests,
    ::testing::Values(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100)
);