#pragma once

#include "datastructs/SparseMatrix.cpp"
#include "datastructs/SparseBoolMatrix.cpp"

/**
 * @brief The MatrixProduct class represents a collection of matrix product operations.
 */
class MatrixProduct {
public:
    /**
     * @brief Computes the matrix-vector product using a naive binary matrix multiplication algorithm.
     * 
     * @tparam N The number of rows in the binary matrix.
     * @tparam M The number of columns in the binary matrix and the size of the vector.
     * @param m The binary matrix.
     * @param vec The vector.
     * @return The resulting vector.
     */
    template <size_t N, size_t M>
    static std::vector<double> naive_bin_matrix_vector(Matrix<N, M, bool> m, Matrix<M, 1, double> vec);

    /**
     * @brief Computes the matrix-vector product using a binary matrix multiplication algorithm optimized for sparse matrices.
     * 
     * @param m The sparse binary matrix.
     * @param vec The vector.
     * @return The resulting vector.
     */
    static inline std::vector<double> bin_matrix_vector(SparseMatrix<bool> m, std::vector<double> vec){
        return std::vector<double>(); // NOT IMPLEMENTED
    }

    /**
     * @brief Computes the matrix-vector product using a binary matrix multiplication algorithm optimized for sparse matrices.
     * 
     * @param m The sparse binary matrix.
     * @param vec The vector.
     * @return The resulting vector.
     */
    static inline std::vector<double> bin_matrix_vector(SparseBoolMatrix m, std::vector<double> vec){
        return std::vector<double>(); // NOT IMPLEMENTED
    }
};
