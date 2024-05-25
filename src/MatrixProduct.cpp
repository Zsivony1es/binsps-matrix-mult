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
    auto ci = m.get_col_indices();
    auto rp = m.get_row_pointers();

    std::vector<double> result = std::vector<double>(rp.size() - 1, 0.0);

    for (size_t i = 1; i < rp.size(); ++i){
        size_t diff = rp[i] - rp[i-1];
        if (diff > 0){
            for (size_t j = 0; j < diff; ++j){
                result[i-1] += vec[ci[rp[i-1] + j]];
            }
        }
    }

    return result;
}

template <size_t N, size_t M>
std::vector<double> MatrixProduct::blas_matrix_vector(RawBoolMatrix<N,M> m, std::vector<double> vec){

    std::vector<double> result(N, 0.0);

    try {
        // BLAS parameters
        const double alpha = 1.0;
        const double beta = 0.0;
        const int leading_dim = M;
        const int incX = 1;
        const int incY = 1;

        cblas_dgemv(CblasRowMajor, CblasNoTrans, N, M, alpha, m.get_data(), leading_dim, vec.data(), incX, beta, result.data(), incY);
    } catch (const std::exception& e){
        std::string message = "Error while performing BLAS matrix-vector multiplication: " + std::string(e.what());
        throw std::invalid_argument(message);
    }

    return result;
}

template <size_t N, size_t M>
std::vector<double> MatrixProduct::ps_bin_matrix_vector(BitsetMatrix<N, M> m, std::vector<double> vec){

    // Analyze what value would be good here
    size_t max_el_count = std::ceil(std::log2(M));

    std::unordered_map<std::bitset<M>, double> partial_sums = PartialSum::precompute_partial_sums<M>(vec, max_el_count);

    std::vector<double> result{};
    for (size_t i = 0; i < N; ++i){
        std::bitset<M> row = m.get_row(i);
        if (partial_sums.find(row) == partial_sums.end()){
            double sum = 0.0;
            for (size_t j = 0; j < M; ++j){
                sum += (row[j]) ? vec[j] : 0.0;
            }
            partial_sums[row] = sum;
        }
        result.push_back(partial_sums[row]);
    }
    return result;
}
