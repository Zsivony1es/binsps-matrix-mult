#include "MatrixProduct.h"

template <size_t N, size_t M, typename T>
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