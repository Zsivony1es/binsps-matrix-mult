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

class SparsityPerformanceTests :
        public ::testing::TestWithParam<double>{
protected:
    static constexpr size_t N = 1000;
    static constexpr size_t M = 1000;
    const int seed = 0;
    RandomMatrixGenerator<N,M,bool> generator; 

    void SetUp() override {
        Utils::test_debug("Setting up SparsityPerformanceTests...");
        generator = RandomMatrixGenerator<N,M,bool>(seed);
    }

    void TearDown() override {}
};

TEST_P(SparsityPerformanceTests, SparsityPerformanceTest) {

    double sparsity = GetParam();

    Utils::test_debug("Sparsity: " + std::to_string(sparsity));

    Matrix<N,M,bool> inputMatrix = generator.generate_generic(sparsity);    
    
    std::vector<double> randomVector = Utils::generate_random_vector(M);

    std::vector<double> correctVec;
    uint naive_time = Utils::time_exec(
        [&correctVec, &inputMatrix, &randomVector](){
            correctVec = MatrixProduct::naive_matrix_vector(inputMatrix, randomVector);
            }
    );

    // =============================
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

    std::stringstream ss;
    ss << N << "," << M << "," << sparsity << "," << naive_time << "," << blas_time << "," << opt_time << "," 
        << Utils::round_to_n_digits(static_cast<double>(naive_time)/naive_time) << "," 
        << Utils::round_to_n_digits(static_cast<double>(naive_time)/blas_time) << "," 
        << Utils::round_to_n_digits(static_cast<double>(naive_time)/opt_time);

    Utils::create_perf_test_header_if_not_exists("sparsity_performance_results.csv");
    Utils::append_to_file("sparsity_performance_results.csv", ss.str());
}

INSTANTIATE_TEST_SUITE_P(
    SparsityTests,
    SparsityPerformanceTests,
    ::testing::Values(0.25, 0.19380169062283858, 0.15023638115308177, 0.11646425864209764, 0.09028388088789624, 0.06998867500826111, 0.05425569416421366, 0.04205938101976114, 0.032604716592719345, 0.025275396791790108, 0.019593658517647973, 0.015189136584827024, 0.011774721396962744, 0.009127843653377167, 0.007075966127061769, 0.005485336792858041, 0.004252270176366191, 0.0032963885966593733, 0.002555382731929735, 0.0019809499745455593, 0.0015356458164247958, 0.0011904430216840571, 0.0009228394807701231, 0.0007153914061870096, 0.0005545762559043692, 0.0004299112638942028, 0.00033327011904199126, 0.0002583532500176503, 0.00020027718652530213, 0.00015525622936715655, 0.00012035567892432856, 9.330053620637767e-05, 7.232720661125343e-05, 5.606853967715304e-05, 4.3464711120743856e-05, 3.3694137990533814e-05, 2.6119923626578664e-05, 2.024834143108148e-05, 1.569665120660823e-05, 1.2168150163830778e-05, 9.432832294011912e-06, 7.31239538376486e-06, 5.668618351505075e-06, 4.394351280069332e-06, 3.406530829072282e-06, 2.6407657353321158e-06, 2.047139456184908e-06, 1.5869563501974161e-06, 1.2302192944516333e-06, 9.5367431640625e-07)
);