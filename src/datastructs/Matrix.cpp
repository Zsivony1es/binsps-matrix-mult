#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include <array>
#include <string>
#include <sstream>

template <size_t N, size_t M, typename T = float>
class Matrix {
private:
    std::array<std::array<T, N>, M> data;
public:
    Matrix(){}

    explicit Matrix(const T& initialValue){
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                data[i][j] = initialValue;
            }
        }
    }

    T& operator[](size_t row, size_t col){
        return data[row][col];
    }

    const T& operator[](size_t row, size_t col) const{
        return data[row][col];
    }

    std::string to_string() const{
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