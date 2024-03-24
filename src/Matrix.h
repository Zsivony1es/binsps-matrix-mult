#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <string>

template <size_t N, size_t M, typename T = float>
class Matrix {
private:
    std::array<std::array<T, N>, M> data;
public:
    Matrix();
    explicit Matrix(const T& initialValue);
    T& operator[](size_t row, size_t col);
    const T& operator[](size_t row, size_t col) const;
    std::string to_string() const;
};

#endif // MATRIX_H
