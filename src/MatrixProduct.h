#pragma once

#include "Matrix.cpp"
#include "SparseMatrix.cpp"

class MatrixProduct {
public:
    template <size_t N, size_t M>
    static std::vector<double> naive_bin_matrix_vector(Matrix<N, M, bool> m, Matrix<M, 1, double> vec);
    static std::vector<double> bin_matrix_vector(SparseMatrix<bool> m, std::vector<double> vec);
};
