#pragma once

#include "Matrix.cpp"
#include <concepts>
#include <vector>
#include <string>

template <typename T>
concept NumericOrBoolean = std::is_arithmetic_v<T> || std::same_as<T, bool>;

template <NumericOrBoolean T>
class SparseMatrix {
private:
    const T DEFAULT_VALUE = static_cast<T>(0);
    std::vector<T> entries;
    std::vector<size_t> col_index;
    std::vector<size_t> row_index;
    size_t col_count = 0;
public:
    SparseMatrix(){}

    template <size_t N, size_t M>
    SparseMatrix(const& Matrix<N, M, T> mx){
        size_t num_elements = 0;
        for (size_t i = 0; i < N; ++i){
            for (size_t j = 0; j < M; ++j){
                if (static_cast<T>(mx[i][j]) != this->DEFAULT_VALUE){
                    this->entries.push_back(static_cast<T>(mx[i][j]));
                    this->col_index.push_back(j);
                    if (this->col_count < j + 1){
                        this->col_count = j + 1;
                    }
                    num_elements++;
                }
            }
            this->row_index.push_back(num_elements);
        }
    }

    SparseMatrix(const& std::vector<T> entries, 
                 const& std::vector<size_t> col_index,
                 const& std::vector<size_t> row_index){
        std::copy(entries.begin(), entries.end(), std::back_inserter(this->entries));
        std::copy(col_index.begin(), col_index.end(), std::back_inserter(this->col_index));
        std::copy(row_index.begin(), row_index.end(), std::back_inserter(this->row_index));
        this->col_count = std::max_element(col_index.begin(), col_index.end()) + 1;
    }
   
    T& operator[](size_t row, size_t col){
        for (size_t i = 0; i < this->row_index.back(); ++i){
            if (this->col_index[i] == col && this->row_index[i] == row)
                return this->entries[i];
        }
        return this->DEFAULT_VALUE;
    }

    const T& operator[](size_t row, size_t col) const {
        for (size_t i = 0; i < this->row_index.back(); ++i){
            if (this->col_index[i] == col && this->row_index[i] == row)
                return this->entries[i];
        }
        return this->DEFAULT_VALUE;
    }

    std::string to_string() const {
        std::stringstream ss;
        for (size_t i = 0; i < (this->row_index.size() - 1); ++i) {
            for (size_t j = 0; j < this->col_count; ++j) {
                ss << this[i][j] << " ";
            }
            ss << std::endl;
        }
        return ss.str();
    }
};
