#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include "IMatrix.cpp"

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
    bool data[N*M];
public:
    RawBoolMatrix() {}

    explicit RawBoolMatrix(bool initialValue) {
        for (size_t i = 0; i < N * M; ++i) {
            data[i] = initialValue;
        }
    }

    explicit RawBoolMatrix(const std::array<std::array<bool, N>, M>& data){
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                this->data[i * N + j] = data[i][j];
            }
        }
    }

    bool operator[](size_t row, size_t col){
        return data[row * N +col];
    }

    const bool operator[](size_t row, size_t col) const override {
        return data[row * N + col];
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