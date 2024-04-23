#pragma GCC diagnostic ignored "-Wpragma-once-outside-header"
#pragma once

#include "../utils/Utils.h"

#include <vector>
#include <iterator>
#include <string>
#include <sstream>

class SparseBoolMatrix {
private:
    std::vector<size_t> col_indices;
    std::vector<size_t> row_pointers;

public:
    SparseBoolMatrix(const size_t numRows, const size_t numCols) {
        row_pointers.resize(numRows + 1, 0);
    }

    SparseBoolMatrix(const std::vector<size_t>& col_indices, const std::vector<size_t>& row_pointers) {
        std::copy(col_indices.begin(), col_indices.end(), std::back_inserter(this->col_indices));
        std::copy(row_pointers.begin(), row_pointers.end(), std::back_inserter(this->row_pointers));
    }

    /**
     * Gets the value at the specified row and column.
     *
     * @param row The row to get the value from.
     * @param col The column to get the value from.
     *
     * @return True if the matrix has a value at the specified row and column, false otherwise.
     */
    const bool operator[](size_t row, size_t col) const {
        for (size_t i = row_pointers[row]; i < row_pointers[row + 1]; i++) {
            if (col_indices[i] == col) {
                return true;
            }
        }
        return false;
    }

    std::string to_string() const {
        std::stringstream ss;

        ss << "Column index: " << Utils::vec_to_str<size_t>(this->col_indices) << std::endl;
        ss << "Row counts: " << Utils::vec_to_str<size_t>(this->row_pointers) << std::endl;

        return ss.str();
    }
};