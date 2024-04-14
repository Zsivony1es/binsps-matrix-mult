#include "MatrixProduct.h"

template <size_t N, size_t M>
std::vector<double> MatrixProduct::bin_matrix_vector(Matrix<N, M, bool> m, Matrix<M, 1, double> vec){
    return std::vector(); // NOT IMPLEMENTED
}

template <size_t N, size_t M>
std::vector<double> MatrixProduct::bin_matrix_vector(SparseMatrix<N, M, bool> m, std::vector<double> vec){
    return std::vector(); // NOT IMPLEMENTED
}