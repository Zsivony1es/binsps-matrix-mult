#include <gtest/gtest.h>

#include "../src/datastructs/SparseBoolMatrix.cpp"
#include "../src/datastructs/BitsetMatrix.cpp"

TEST(DatastructTest, test_sparse_binary_constructor_with_lists) {
    std::array<std::array<bool, 5>, 5> matrixData = {{
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true}
    }};

    const std::vector<size_t> col_indices = {0,2,3,4,1,3,4};
    const std::vector<size_t> row_pointers = {0,3,4,5,6,7};
    const SparseBoolMatrix matrix = SparseBoolMatrix(col_indices,row_pointers);

    for(size_t i = 0; i<matrixData.size();i++){
        for(size_t j = 0; j<matrixData.at(i).size();j++){
            bool resultValue = matrix[i,j];
            ASSERT_EQ(matrixData.at(i).at(j), resultValue);
        } 
    }
}

TEST(DatastructTest, test_sparse_binary_constructor_with_matrix) {
    std::array<std::array<bool, 5>, 5> matrixData = {{
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true}
    }};

    Matrix<5,5,bool> matrix = Matrix<5,5,bool>(matrixData);

    const std::vector<size_t> col_indices = {0,2,3,4,1,3,4};
    const std::vector<size_t> row_pointers = {0,3,4,5,6,7};

    const SparseBoolMatrix sparse_bool_matrix = SparseBoolMatrix(matrix);

    ASSERT_EQ(sparse_bool_matrix.get_col_indices(), col_indices);
    ASSERT_EQ(sparse_bool_matrix.get_row_pointers(), row_pointers);

    for(size_t i = 0; i<matrixData.size();i++){
        for(size_t j = 0; j<matrixData.at(i).size();j++){
            bool resultValue = sparse_bool_matrix[i,j];
            ASSERT_EQ(matrixData.at(i).at(j), resultValue);
        } 
    }
}

TEST(DatastructTest, test_bitset_matrix_constructor) {
    std::array<std::array<bool, 5>, 5> matrixData = {{
        {true, false, true, true, false},
        {false, false, false, false, true},
        {false, true, false, false, false},
        {false, false, false, true, false},
        {false, false, false, false, true}
    }};

    BitsetMatrix<5,5> matrix = BitsetMatrix<5,5>(matrixData);

    for(size_t i = 0; i < matrixData.size(); i++){
        for(size_t j = 0; j < matrixData.at(i).size(); j++){
            bool resultValue = matrix[i,j];
            ASSERT_EQ(matrixData.at(i).at(j), resultValue);
        } 
    }
}