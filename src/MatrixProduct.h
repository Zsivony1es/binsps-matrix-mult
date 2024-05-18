#pragma once

#include "datastructs/SparseMatrix.cpp"
#include "datastructs/SparseBoolMatrix.cpp"
#include "datastructs/RawBoolMatrix.cpp"

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
    template <size_t N, size_t M, NumericOrBoolean T>
    static std::vector<double> naive_bin_matrix_vector(Matrix<N, M, T> m, std::vector<double> vec);

    /**
     * @brief Computes the matrix-vector product using a binary matrix multiplication algorithm optimized for sparse matrices.
     * 
     * @param m The sparse binary matrix.
     * @param vec The vector.
     * @return The resulting vector.
     */
    static inline std::vector<double> bin_matrix_vector(SparseBoolMatrix m, std::vector<double> vec);

    /**
     * @brief Computes the matrix-vector product using a binary matrix multiplication algorithm optimized for sparse matrices,
     * while excluding elements that are below a certain threshold for faster computation.
     * 
     * @param m The sparse binary matrix.
     * @param vec The vector.
     * @param threshold The threshold below which elements are set to zero.
     * @return The resulting vector.
     */
    static inline std::vector<double> bin_matrix_vector(SparseBoolMatrix m, std::vector<double> vec, double threshold){
        for (double& entry : vec){
            if (std::abs(entry) < threshold) 
                entry = 0.0;
        }
        return bin_matrix_vector(m, vec);
    }

    /**
     * @brief Computes the matrix-vector product using the BLAS library for a raw boolean matrix and a vector.
     *
     * @tparam N the number of rows in the raw boolean matrix
     * @tparam M the number of columns in the raw boolean matrix and the size of the vector
     *
     * @param m the raw boolean matrix
     * @param vec the vector
     *
     * @return the resulting vector
     *
     * @throws None
     */
    template <size_t N, size_t M>
    static std::vector<double> blas_matrix_vector(RawBoolMatrix<N,M> m, std::array<double, M> vec);
};
