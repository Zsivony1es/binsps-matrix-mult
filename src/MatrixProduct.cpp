#include "MatrixProduct.h"

#include <cblas.h>

template <size_t N, size_t M, NumericOrBoolean T>
std::vector<double> MatrixProduct::naive_bin_matrix_vector(Matrix<N, M, T> m, std::vector<double> vec){
    auto ret_val = std::vector<double>();
    for (size_t i = 0; i < N; ++i){
        double entry = 0.0;
        for (size_t j = 0; j < M; ++j){
            entry += (static_cast<double>(m[i,j]) * vec[j]);
        }
        ret_val.push_back(entry);
    }
    return ret_val;
}

std::vector<double> MatrixProduct::bin_matrix_vector(SparseBoolMatrix m, std::vector<double> vec){

}

template <size_t N, size_t M>
std::vector<double> MatrixProduct::blas_matrix_vector(RawBoolMatrix<N,M> m, std::array<double, M> vec){
    double doubleMatrix[N * M];
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            doubleMatrix[i * M + j] = static_cast<double>(m.data[i][j]);
        }
    }

    std::vector<double> result(N, 0.0);

    // BLAS parameters
    const double alpha = 1.0;
    const double beta = 0.0;
    const int lda = M; // Leading dimension of the matrix
    const int incX = 1; // Increment for elements of x
    const int incY = 1; // Increment for elements of y

    cblas_dgemv(CblasRowMajor, CblasNoTrans, N, M, alpha, doubleMatrix, lda, vec.data(), incX, beta, result.data(), incY);

    return result;
}