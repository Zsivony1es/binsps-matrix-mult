#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include "IMatrix.cpp"

#include <string>
#include <sstream>

template <size_t N, size_t M>
class RawBoolMatrix : public IMatrix<bool> {
private:
    bool data[N][M];
public:
    RawBoolMatrix() {}

    explicit RawBoolMatrix(bool initialValue) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                data[i][j] = initialValue;
            }
        }
    }

    explicit RawBoolMatrix(const std::array<std::array<bool, N>, M>& data){
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                this->data[i][j] = data[i][j];
            }
        }
    }

    bool operator[](size_t row, size_t col){
        return data[row][col];
    }

    const bool operator[](size_t row, size_t col) const override {
        return data[row][col];
    }

    std::string to_string() const override {
        std::stringstream ss;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                ss << data[i][j] << " ";
            }
            ss << std::endl;
        }
        return ss.str();
    }
};