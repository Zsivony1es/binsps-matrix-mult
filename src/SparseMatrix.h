#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <string>

template <typename T>
class SparseMatrix {
private:
    std::vector<T> entries;
    std::vector<size_t> col_index;
    std::vector<size_t> row_index;
public:
    Matrix();
    template <size_t N, size_t M>
    Matrix(Matrix<N, M, T> mx);
    T& operator[](size_t row, size_t col);
    const T& operator[](size_t row, size_t col) const;
    std::string to_string() const;
};

#endif // SPARSEMATRIX_H
