#pragma once

#include "datastructs/SparseMatrix.cpp"
#include "datastructs/SparseBoolMatrix.cpp"
#include "datastructs/RawBoolMatrix.cpp"
#include "datastructs/BitsetMatrix.cpp"
#include "PartialSum.cpp"

/**
 * @brief The MatrixProduct class represents a collection of matrix product operations.
 */
class MatrixProduct {
    static void remove_values_below_threshold(std::vector<double>& vec, double threshold){
        if (threshold != -1.0){
            for (double& entry : vec){
            if (std::abs(entry) < threshold) 
                entry = 0.0;
            }
        }
    }
public:
    /**
     * @brief Computes the matrix-vector product using a naive binary matrix multiplication algorithm.
     * 
     * @tparam N The number of rows in the binary matrix.
     * @tparam M The number of columns in the binary matrix and the size of the vector.
     * @param m The binary matrix.
     * @param vec The vector.
     * @param threshold The threshold below which the entries in the vector are set to 0.
     * 
     * @return The resulting vector.
     */
    template <size_t N, size_t M, NumericOrBoolean T>
    static std::vector<double> naive_bin_matrix_vector(Matrix<N, M, T> m, std::vector<double> vec, double threshold = -1.0);

    /**
     * @brief Computes the matrix-vector product using a binary matrix multiplication algorithm optimized for sparse matrices.
     * 
     * @param m The matrix.
     * @param vec The vector.
     * @param threshold The threshold below which the entries in the vector are set to 0.
     * 
     * @return The resulting vector.
     */
    static inline std::vector<double> bin_matrix_vector(SparseBoolMatrix m, std::vector<double> vec, double threshold = -1.0);

    /**
     * @brief Computes the matrix-vector product using the BLAS library for a raw boolean matrix and a vector.
     *
     * @tparam N the number of rows in the raw boolean matrix
     * @tparam M the number of columns in the raw boolean matrix and the size of the vector
     *
     * @param m the sparse binary matrix
     * @param vec the vector
     * @param threshold the threshold below which the entries in the vector are set to 0
     *
     * @return the resulting vector
     *
     * @throws None
     */
    template <size_t N, size_t M>
    static std::vector<double> blas_matrix_vector(RawBoolMatrix<N,M> m, std::vector<double> vec, double threshold = -1.0);

    /**
     * Computes the matrix-vector product of a vector and many different binary matrices.
     *
     * @tparam N The number of rows in the binary matrix.
     * @tparam M The number of columns in the binary matrix and the size of the vector.
     *
     * @param m A list of binary matrices
     * @param vec The vector.
     * @param max_sum_term_count The maximum number of terms in the partial sums.
     * @param threshold The threshold below which the entries in the vector are set to 0.
     *
     * @return The resulting vectors.
     *
     * @throws None
     */
    template <size_t N, size_t M>
    static std::vector<std::vector<double>> ps_bin_matrix_vector(std::vector<BitsetMatrix<N, M>> m, std::vector<double> vec, size_t max_sum_term_count = 0, double threshold = -1.0);

};