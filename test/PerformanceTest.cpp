#include <gtest/gtest.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>
#include "../src/RandomMatrixGenerator.cpp"
#include "../src/MatrixType.cpp"
#include "../src/MatrixProduct.cpp"

TEST(MatrixPerformanceTest, MatrixPerformanceTest) {

    const size_t N = 5000;
    const size_t M = 5000;

    double sparsity = 1 / N;

    RandomMatrixGenerator<N,M,bool> generator;
    Matrix<N,M,bool> inputMatrix = generator.generate_generic(sparsity);    
    
    std::vector<double> randomVector = Utils::generate_random_vector(M);

    std::vector<double> correctVec;
    uint time = Utils::time_exec(
        [&correctVec, &inputMatrix, &randomVector](){
            correctVec = MatrixProduct::naive_bin_matrix_vector(inputMatrix, randomVector);
            }
    );

    Utils::write_to_file("performance_results.csv", std::to_string(time));
    EXPECT_EQ(true,true);

    // Enhanced Algorithms
    std::vector<double> resultVec;
    SparseBoolMatrix sparse_bool_matrix = SparseBoolMatrix(inputMatrix);
    time = Utils::time_exec(
        [&resultVec, &sparse_bool_matrix, &randomVector](){
            resultVec = MatrixProduct::bin_matrix_vector(sparse_bool_matrix, randomVector);
            }
    );

    Utils::write_to_file("performance_results.csv", std::to_string(time));

    EXPECT_EQ(resultVec.size(), correctVec.size());
    for(int i = 0; i<resultVec.size();i++){
        EXPECT_EQ(resultVec.at(i), correctVec.at(i));
    }
}