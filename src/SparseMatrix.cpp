#include "Matrix.cpp"
#include "utils/Utils.cpp"

#include <concepts>

template <typename T>
concept NumericOrBoolean = std::is_arithmetic_v<T> || std::same_as<T, bool>;

template <NumericOrBoolean T>
class SparseMatrix {
private:
    const T DEFAULT_VALUE = static_cast<T>(0);
    std::vector<T> entries;
    std::vector<size_t> col_index;
    std::vector<size_t> row_count;
    size_t col_count = 0;
public:
    SparseMatrix<T>(){}

    template <size_t N, size_t M>
    SparseMatrix<N, M, T>(const Matrix<N,M,T>& mx){
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
            this->row_count.push_back(num_elements);
        }
    }

    SparseMatrix<T>(const std::vector<T>& entries, 
                    const std::vector<size_t>& col_index,
                    const std::vector<size_t>& row_count){
        std::copy(entries.begin(), entries.end(), std::back_inserter(this->entries));
        std::copy(col_index.begin(), col_index.end(), std::back_inserter(this->col_index));
        std::copy(row_count.begin(), row_count.end(), std::back_inserter(this->row_count));
        this->col_count = *std::max_element(col_index.begin(), col_index.end()) + 1;
    }

    std::string to_string() const {
        std::stringstream ss;
        bool first = true;

        ss << "Entries: " << Utils::vec_to_str<T>(this->entries) << std::endl;
        ss << "Column index: " << Utils::vec_to_str<size_t>(this->col_index) << std::endl;
        ss << "Row counts: " << Utils::vec_to_str<size_t>(this->row_count) << std::endl;

        return ss.str();
    }
};
