#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include <vector>
#include <iterator>

class SparseBoolMatrix {
private:
    std::vector<size_t> col_indices;
    std::vector<size_t> row_pointers;

public:
    SparseBoolMatrix(size_t numRows, size_t numCols) {
        row_pointers.resize(numRows + 1, 0);
    }

    SparseBoolMatrix(const std::vector<size_t>& col_indices, const std::vector<size_t>& row_pointers) {
        std::copy(col_indices.begin(), col_indices.end(), std::back_inserter(this->col_indices));
        std::copy(row_pointers.begin(), row_pointers.end(), std::back_inserter(this->row_pointers));
    }

    bool exists(size_t row, size_t col) const {
        for (size_t i = row_pointers[row]; i < row_pointers[row + 1]; i++) {
            if (col_indices[i] == col) {
                return true;
            }
        }
        return false;
    }
};