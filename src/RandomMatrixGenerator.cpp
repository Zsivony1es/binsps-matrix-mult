#pragma once

#include "Matrix.cpp"

template<size_t N, size_t M, typename T = float>
class RandomMatrixGenerator{
    Matrix<N,M,T> matrix;
public:
    RandomMatrixGenerator();
    Matrix<N,M,T>& get_new_matrix(float sparsity);
    Matrix<N,M,T> get_matrix();
};