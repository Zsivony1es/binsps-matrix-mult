#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include <random>

#include "datastructs/Matrix.cpp"
#include "datastructs/RawBoolMatrix.cpp"
#include "datastructs/SparseBoolMatrix.cpp"

template<size_t N, size_t M, NumericOrBoolean T>
class RandomMatrixGenerator{
    enum MatrixType { GENERIC, SPARSEBOOL, RAWBOOL };
    std::mt19937 mt;
public:
    RandomMatrixGenerator(){}

    RandomMatrixGenerator(int seed){
        this->mt = std::mt19937(seed);
    }

    /**
     * Generates a matrix based on the given sparsity and matrix type.
     *
     * @param sparsity The sparsity of the matrix.
     * @param type The type of the matrix. Defaults to GENERIC.
     *
     * @return The generated matrix.
     *
     * @throws None
     */
    IMatrix<T> generate(float sparsity, MatrixType type = GENERIC){
        switch (type) {
        case GENERIC:
            return generate_generic(sparsity);
        case SPARSEBOOL:
            return generate_sparse_bool(sparsity);
        case RAWBOOL:
            return generate_raw_bool(sparsity);
        default:
            break;
        }
    }

private:
    Matrix<N,M,T> generate_generic(float sparsity){
        
        std::array<std::array<T, N>, M> data;
        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        for (size_t i = 0; i < N; ++i){
            for (size_t j = 0; j < M; ++j){
                if (distribution(this->mt) < sparsity){
                    data[i][j] = static_cast<T>(this->mt() % 2);
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
                    entries[i][j] = true;
                else
                    entries[i][j] = false;
            }
        }

        return RawBoolMatrix<N,M>(entries);
    }
};