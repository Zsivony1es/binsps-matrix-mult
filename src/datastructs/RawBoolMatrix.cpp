#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include "Matrix.cpp"

#include <string>
#include <sstream>


/**
 * @brief A class representing a boolean matrix.
 * 
 * This class represents a matrix of boolean values stored in a contiguous block of memory,
 * stored in row major order. It provides an interface for accessing and manipulating the matrix elements.
 * 
 * @tparam N the number of rows in the matrix
 * @tparam M the number of columns in the matrix
 */
template <size_t N, size_t M>
class RawBoolMatrix : public IMatrix<bool> {
private:
    double data[N*M];
public:
    RawBoolMatrix() {}

    explicit RawBoolMatrix(bool initialValue) {
        for (size_t i = 0; i < N * M; ++i) {
            data[i] = initialValue ? 1.0 : 0.0;
        }
    }

    explicit RawBoolMatrix(const std::array<std::array<bool, M>, N>& data){
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                this->data[i * M + j] = data[i][j] ? 1.0 : 0.0;
            }
        }
    }

    explicit RawBoolMatrix(const Matrix<N,M,bool>& data){
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                this->data[i * M + j] = data[i,j] ? 1.0 : 0.0;
            }
        }
    }

    bool operator[](size_t row, size_t col){
        return (data[row * N +col] == 1.0) ? true : false;
    }

    const bool operator[](size_t row, size_t col) const override {
        return (data[row * N + col] == 1.0) ? true : false;
    }

    const double* get_data() const {
        return data;
    }

    std::string to_string() const override {
        std::stringstream ss;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                ss << data[i * N + j] << " ";
            }
            ss << std::endl;
        }
        return ss.str();
    }
};