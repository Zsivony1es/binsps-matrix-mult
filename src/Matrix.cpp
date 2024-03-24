#include "Matrix.h"

#include <sstream>

template<size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix() {}

template<size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const T& initialValue) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            data[i][j] = initialValue;
        }
    }
}

template<size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator[](size_t row, size_t col) {
    return data[row][col];
}

template<size_t N, size_t M, typename T>
const T& Matrix<N, M, T>::operator[](size_t row, size_t col) const {
    return data[row][col];
}

template<size_t N, size_t M, typename T>
std::string Matrix<N, M, T>::to_string() const {
    std::stringstream ss;
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            ss << data[i][j] << " ";
        }
        ss << std::endl;
    }
    return ss.str();
}
