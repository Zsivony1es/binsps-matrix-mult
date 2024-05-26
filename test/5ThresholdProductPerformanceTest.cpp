#include <gtest/gtest.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include <sstream>

#include "../src/RandomMatrixGenerator.cpp"
#include "../src/MatrixType.cpp"
#include "../src/MatrixProduct.cpp"

class ThresholdProductPerformanceTests :
        public ::testing::TestWithParam<double>{
protected:
    static constexpr size_t N = 30;
    static constexpr size_t M = 30;
    const int seed = 0;
    RandomMatrixGenerator<N,M,bool> generator; 

    void SetUp() override {
        Utils::test_debug("Setting up ThresholdProductPerformanceTests...");
        generator = RandomMatrixGenerator<N,M,bool>(seed);
    }

    void TearDown() override {}
};

TEST_P(ThresholdProductPerformanceTests, ThresholdProductPerformanceTest) {

    double sparsity = 0.05;
    double threshold = GetParam();

    Matrix<N,M,bool> inputMatrix = generator.generate_generic(sparsity);  
    
    std::vector<double> randomVector = Utils::generate_random_vector(M);

    std::vector<double> correctVec;
    uint naive_time = Utils::time_exec(
        [&correctVec, &inputMatrix, &randomVector, &threshold](){
            correctVec = MatrixProduct::naive_bin_matrix_vector(inputMatrix, randomVector, threshold);
            }
    );

    // =============================
    // ==== Enhanced Algorithms ====
    // =============================

    // Multiplication with optimized data structure
    std::vector<double> resultVec;
    SparseBoolMatrix sparse_bool_matrix = SparseBoolMatrix(inputMatrix);
    uint opt_time = Utils::time_exec(
        [&resultVec, &sparse_bool_matrix, &randomVector, &threshold](){
            resultVec = MatrixProduct::bin_matrix_vector(sparse_bool_matrix, randomVector, threshold);
            }
    );

    EXPECT_EQ(resultVec.size(), correctVec.size());
    for(int i = 0; i < resultVec.size(); i++){
        EXPECT_EQ(resultVec.at(i), correctVec.at(i));
    }

    // Multiplication with BLAS
    resultVec.clear();
    RawBoolMatrix<N,M> raw_bool_matrix = RawBoolMatrix<N,M>(inputMatrix);
    uint blas_time = Utils::time_exec(
        [&resultVec, &raw_bool_matrix, &randomVector, &threshold](){
            resultVec = MatrixProduct::blas_matrix_vector(raw_bool_matrix, randomVector, threshold);
            }
    );

    EXPECT_EQ(resultVec.size(), correctVec.size());
    for(int i = 0; i < resultVec.size(); i++){
        EXPECT_LT(std::abs(resultVec.at(i) - correctVec.at(i)), 0.0001);
    }

    std::stringstream ss;
    ss << N << "," << M << "," << sparsity << "," << naive_time << "," << blas_time << "," << opt_time << "," 
        << static_cast<double>(naive_time)/opt_time << "," << static_cast<double>(blas_time)/opt_time;

    Utils::create_perf_test_header_if_not_exists();
    Utils::append_to_file("performance_results.csv", ss.str());
}

INSTANTIATE_TEST_SUITE_P(
    ThresholdProductPerformanceTests,
    ThresholdProductPerformanceTests,
    ::testing::Values(-1.0, 0.05, 0.01, 0.1, 0.0005)
);