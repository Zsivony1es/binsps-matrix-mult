#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include "IMatrix.cpp"

#include <array>
#include <sstream>
#include <concepts>

template <typename T>
concept NumericOrBoolean = std::is_arithmetic_v<T> || std::same_as<T, bool>;

template <size_t N, size_t M, NumericOrBoolean T>
class Matrix : public IMatrix<T> {
private:
    std::array<std::array<T, M>, N> data;
public:
    Matrix() {}

    explicit Matrix(const std::array<std::array<T, M>, N>& data) : data(data) {}

    explicit Matrix(const T& initialValue) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                data[i][j] = initialValue;
            }
        }
    }

    T& operator[](size_t row, size_t col){
        return data[row][col];
    }

    const T operator[](size_t row, size_t col) const override {
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