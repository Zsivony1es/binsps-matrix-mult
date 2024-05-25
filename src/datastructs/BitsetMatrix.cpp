#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include "Matrix.cpp"

#include <string>
#include <sstream>
#include <bitset>

/**
 * @brief A class representing a boolean matrix using a bitset.
 * 
 * This class represents a matrix of boolean values stored in a bitset, stored in row major order. 
 * It provides an interface for accessing and manipulating the matrix elements.
 * 
 * @tparam N the number of rows in the matrix
 * @tparam M the number of columns in the matrix
 */
template <size_t N, size_t M>
class BitsetMatrix : public IMatrix<bool> {
private:
    std::bitset<N*M> data;
public:
    BitsetMatrix() {}

    explicit BitsetMatrix(bool initialValue) {
        if (initialValue) {
            data |= true;
        } else {
            data &= false;
        }
    }

    explicit BitsetMatrix(std::bitset<N*M> data) {
        this->data = data;
    }

    explicit BitsetMatrix(const std::array<std::array<bool, M>, N>& data){
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                this->data[i * M + j] = data[i][j];
            }
        }
    }

    explicit BitsetMatrix(const Matrix<N,M,bool>& data){
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                this->data[i * M + j] = data[i,j];
            }
        }
    }

    bool operator[](size_t row, size_t col){
        return data[row * N +col];
    }

    const bool operator[](size_t row, size_t col) const override {
        return data[row * N +col];
    }

    std::bitset<M> get_row(size_t index) {
        std::bitset<M> row;
        for (size_t j = 0; j < M; ++j) {
            row[j] = data[index * M + j];
        }
        return row;
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