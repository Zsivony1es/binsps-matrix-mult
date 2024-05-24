#include <gtest/gtest.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>

#include "../src/RandomMatrixGenerator.cpp"
#include "../src/MatrixType.cpp"
#include "../src/MatrixProduct.cpp"

TEST(MatrixPerformanceTest, MatrixPerformanceTest) {

    const size_t N = 2000;
    const size_t M = 1000;

    double sparsity = 1 / N;

    Utils::test_debug("Checkpoint 1");

    RandomMatrixGenerator<N,M,bool> generator;
    Matrix<N,M,bool> inputMatrix = generator.generate_generic(sparsity);    
    
    std::vector<double> randomVector = Utils::generate_random_vector(M);

    std::vector<double> correctVec;
    uint naive_time = Utils::time_exec(
        [&correctVec, &inputMatrix, &randomVector](){
            correctVec = MatrixProduct::naive_bin_matrix_vector(inputMatrix, randomVector);
            }
    );

    Utils::test_debug("Naive product finished performance test calculations.");

    // ==== Enhanced Algorithms ====
    // =============================

    // Multiplication with optimized data structure
    std::vector<double> resultVec;
    SparseBoolMatrix sparse_bool_matrix = SparseBoolMatrix(inputMatrix);
    uint opt_time = Utils::time_exec(
        [&resultVec, &sparse_bool_matrix, &randomVector](){
            resultVec = MatrixProduct::bin_matrix_vector(sparse_bool_matrix, randomVector);
            }
    );

    EXPECT_EQ(resultVec.size(), correctVec.size());
    for(int i = 0; i<resultVec.size();i++){
        EXPECT_EQ(resultVec.at(i), correctVec.at(i));
    }

    Utils::test_debug("Product with optimized data structure finished performance test calculations.");

    // Multiplication with BLAS
    resultVec.clear();
    RawBoolMatrix<N,M> raw_bool_matrix = RawBoolMatrix<N,M>(inputMatrix);
    uint blas_time = Utils::time_exec(
        [&resultVec, &raw_bool_matrix, &randomVector](){
            resultVec = MatrixProduct::blas_matrix_vector(raw_bool_matrix, randomVector);
            }
    );

    EXPECT_EQ(resultVec.size(), correctVec.size());
    for(int i = 0; i<resultVec.size();i++){
        EXPECT_LT(std::abs(resultVec.at(i) - correctVec.at(i)), 0.0001);
    }

    Utils::test_debug("Product with BLAS finished performance test calculations.");
    Utils::test_debug("Writing to performance_results.csv...");

    std::string data_to_write = std::to_string(N) + "," + std::to_string(M) + "," 
                                + std::to_string(sparsity) + "," + std::to_string(naive_time) + "," 
                                + std::to_string(opt_time) + "," + std::to_string(blas_time);

    Utils::create_perf_test_header_if_not_exists();
    Utils::append_to_file("performance_results.csv", data_to_write);
}