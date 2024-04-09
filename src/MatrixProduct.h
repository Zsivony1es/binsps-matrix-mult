#ifndef MATRIXPRODUCT_H
#define MATRIXPRODUCT_H

#include "Matrix.h"

class MatrixProduct {
public:
    template <size_t N, size_t M>
    static Matrix<N, 1, double> opt_bin_matrix_vector(Matrix<N, M, bool> m, Matrix<M, 1, double> vec);
};

#endif // MATRIXPRODUCT_H