#include <gtest/gtest.h>

#include "../src/MatrixProduct.cpp"

TEST(ProductTest, test_naive_matrix_multiplication_for_binary_values) {
    std::vector<double> randomVector = {1,2,3,4,5};

    std::array<std::array<bool, 5>, 5> matrixData = {{
        {true, false, true, false, true},
        {false, true, false, true, false},
        {true, true, true, true, true},
        {false, false, false, false, false},
        {false, false, false, false, false}
    }};
    Matrix<5,5,bool> matrix = Matrix<5,5,bool>(matrixData);

    std::vector<double> correctVec = {9,6,15,0,0};

    std::vector<double> resultVec = {};
    uint time = Utils::time_exec(
        [&resultVec, &matrix, &randomVector](){
            resultVec = MatrixProduct::naive_bin_matrix_vector(matrix, randomVector);
            }
    );

    ASSERT_EQ(resultVec.size(), correctVec.size());
    for(int i = 0; i<resultVec.size();i++){
        ASSERT_EQ(resultVec.at(i), correctVec.at(i));
    }
}

TEST(ProductTest, test_sparse_binary_matrix_multiplication_for_binary_values) {
    std::vector<double> randomVector = {1,2,3,4,5};

    std::array<std::array<bool, 5>, 5> matrixData = {{
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true}
    }};

    Matrix<5,5,bool> matrix = Matrix<5,5,bool>(matrixData);
    const SparseBoolMatrix sparse_bool_matrix = SparseBoolMatrix(matrix);

    std::vector<double> correctVec = {8,5,2,4,5};

    std::vector<double> resultVec = {};
    uint time = Utils::time_exec(
        [&resultVec, &sparse_bool_matrix, &randomVector](){
            resultVec = MatrixProduct::bin_matrix_vector(sparse_bool_matrix, randomVector);
            }
    );

    ASSERT_EQ(resultVec.size(), correctVec.size());
    for(int i = 0; i<resultVec.size();i++){
        ASSERT_EQ(resultVec.at(i), correctVec.at(i));
    }
}
