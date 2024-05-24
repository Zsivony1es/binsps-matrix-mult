#include <gtest/gtest.h>

#include "../src/MatrixProduct.cpp"

TEST(ProductTest, test_naive_square_matrix_multiplication_for_binary_values) {
    
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

    resultVec = MatrixProduct::naive_bin_matrix_vector(matrix, randomVector);

    ASSERT_EQ(resultVec.size(), correctVec.size());
    for (int i = 0; i < resultVec.size(); i++){
        ASSERT_EQ(resultVec.at(i), correctVec.at(i));
    }
}

TEST(ProductTest, test_naive_matrix_multiplication_for_binary_values) {
    
    std::vector<double> randomVector = {1,2,3,4,5};
    std::array<std::array<bool, 5>, 10> matrixData = {{
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true},
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true}
    }};
    Matrix<10,5,bool> matrix = Matrix<10,5,bool>(matrixData);

    std::vector<double> correctVec = {8,5,2,4,5,8,5,2,4,5};
    std::vector<double> resultVec = {};

    resultVec = MatrixProduct::naive_bin_matrix_vector(matrix, randomVector);

    ASSERT_EQ(resultVec.size(), correctVec.size());
    for (int i = 0; i < resultVec.size(); i++){
        ASSERT_EQ(resultVec.at(i), correctVec.at(i));
    }
}

TEST(ProductTest, test_sparse_square_binary_matrix_multiplication_for_binary_values) {
    
    std::vector<double> inputVector = {1,2,3,4,5};
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
    resultVec = MatrixProduct::bin_matrix_vector(sparse_bool_matrix, inputVector);

    ASSERT_EQ(resultVec.size(), correctVec.size());
    for (int i = 0; i < resultVec.size(); i++){
        ASSERT_EQ(resultVec.at(i), correctVec.at(i));
    }
}

TEST(ProductTest, test_sparse_binary_matrix_multiplication_for_binary_values) {
    
    std::array<std::array<bool, 5>, 10> matrixData = {{
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true},
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true}
    }};

    Matrix<10,5,bool> matrix = Matrix<10,5,bool>(matrixData);
    const SparseBoolMatrix sparse_bool_matrix = SparseBoolMatrix(matrix);

    std::vector<double> inputVector = {1,2,3,4,5};
    std::vector<double> correctVec = {8,5,2,4,5,8,5,2,4,5};
    std::vector<double> resultVec = {};
    resultVec = MatrixProduct::bin_matrix_vector(sparse_bool_matrix, inputVector);

    Utils::test_debug("correctVec size: " + std::to_string(correctVec.size()));
    Utils::test_debug("resultVec size: " + std::to_string(resultVec.size()));

    ASSERT_EQ(resultVec.size(), correctVec.size());
    for (int i = 0; i < resultVec.size(); i++){
        ASSERT_EQ(resultVec.at(i), correctVec.at(i));
    }
}

TEST(ProductTest, test_blas_square_matrix_multiplication_for_binary_values) {

    std::vector<double> inputVector = {1,2,3,4,5};
    std::array<std::array<bool, 5>, 5> matrixData = {{
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true}
    }};

    const RawBoolMatrix<5,5> matrix(matrixData);
    const std::vector<double> correctVec = {8,5,2,4,5};

    std::vector<double> resultVec = {};
    resultVec = MatrixProduct::blas_matrix_vector(matrix, inputVector);

    ASSERT_EQ(resultVec.size(), correctVec.size());
    for (int i = 0; i < resultVec.size(); i++){
        ASSERT_EQ(resultVec.at(i), correctVec.at(i));
    }
}

TEST(ProductTest, test_blas_matrix_multiplication_for_binary_values) {

    std::vector<double> inputVector = {1,2,3,4,5};
    std::array<std::array<bool, 5>, 10> matrixData = {{
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true},
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true}
    }};

    const RawBoolMatrix<10,5> matrix(matrixData);
    const std::vector<double> correctVec = {8,5,2,4,5,8,5,2,4,5};

    std::vector<double> resultVec = {};
    resultVec = MatrixProduct::blas_matrix_vector(matrix, inputVector);

    Utils::test_debug("Correct: " + Utils::vec_to_str(correctVec));
    Utils::test_debug("Result: " + Utils::vec_to_str(resultVec));

    ASSERT_EQ(resultVec.size(), correctVec.size());
    for (int i = 0; i < resultVec.size(); i++){
        ASSERT_EQ(resultVec.at(i), correctVec.at(i));
    }
}
