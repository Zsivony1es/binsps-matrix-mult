#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include "datastructs/Matrix.cpp"
#include "datastructs/RawBoolMatrix.cpp"
#include "datastructs/SparseBoolMatrix.cpp"
#include "datastructs/BitsetMatrix.cpp"
#include "MatrixType.cpp"

template<size_t N, size_t M, NumericOrBoolean T>
class RandomMatrixGenerator{
    std::mt19937 mt;
public:
    RandomMatrixGenerator(){}

    RandomMatrixGenerator(int seed){
        this->mt = std::mt19937(seed);
    }

    Matrix<N,M,T> generate_generic(float sparsity){
        
        std::array<std::array<T, M>, N> data;
        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        for (size_t i = 0; i < N; ++i){
            for (size_t j = 0; j < M; ++j){
                if (distribution(this->mt) < sparsity){
                    data[i][j] = static_cast<T>(1);
                } else {
                    data[i][j] = static_cast<T>(0);
                }
            }
        }
        return Matrix<N,M,T>(data);
    }

    SparseBoolMatrix generate_sparse_bool(float sparsity){

        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        std::vector<size_t> col_indices;
        std::vector<size_t> row_pointers;

        size_t element_count = 0;
        row_pointers.push_back(element_count);

        for (size_t i = 0; i < N; ++i){
            
            for (size_t j = 0; j < M; ++j){
                if (distribution(this->mt) < sparsity){
                    col_indices.push_back(i);
                    element_count++;
                }
            }
            row_pointers.push_back(element_count);
        }

        return SparseBoolMatrix(col_indices, row_pointers);
    }

    RawBoolMatrix<N,M> generate_raw_bool(float sparsity){

        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::array<std::array<bool, N>, M> data;

        for (size_t i = 0; i < N; ++i){
            for (size_t j = 0; j < M; ++j){
                if (distribution(this->mt) < sparsity)
                    data[i][j] = true;
                else
                    data[i][j] = false;
            }
        }

        return RawBoolMatrix<N,M>(data);
    }

    BitsetMatrix<N,M> generate_bitset_matrix(float sparsity){

        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::bitset<N*M> data;

        for (size_t i = 0; i < N; ++i){
            for (size_t j = 0; j < M; ++j){
                if (distribution(this->mt) < sparsity)
                    data[i * N + j] = 1;
                else
                    data[i * N + j] = 0;
            }
        }

        return BitsetMatrix<N,M>(data);
    }
};