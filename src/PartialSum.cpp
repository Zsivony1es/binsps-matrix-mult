#pragma once

#include <cmath>

class PartialSum {

    /**
    * This is the recursive function that contains the computation logic, the public method just calls this with certain parameters.
    * 
    * @param vec The vector to be multiplied with the matrix.
    * @param max_element_count The maximum number of elements to consider in the multiplication. A value of 0 will calculate all partial sums.
    * @param partial_sums A vector containing the previously computed partial sums.
    * @param index_to_add The index of the element to add to the partial sums.
    *
    * @return A vector containing the partial sums of the multiplication.
    *
    * @throws None.
    */
    static std::vector<double> _precompute_partial_sums(const std::vector<double>& vec, 
                                                        size_t max_element_count, 
                                                        const std::vector<double> partial_sums,
                                                        size_t index_to_add) {

        auto ret_val = std::vector<double>();

        if (static_cast<size_t>(std::pow(2, max_element_count)) == partial_sums.size()){
            return partial_sums;
        }

        for (size_t i = 0; i < partial_sums.size(); ++i){
            ret_val.push_back(partial_sums[i]);
            ret_val.push_back(partial_sums[i] + vec[index_to_add]);
        }

        return _precompute_partial_sums(vec, max_element_count, ret_val, index_to_add + 1);
    }

public:

    /**
    * Computes all combinations of sums of elements in the vector. If max_element_count is specified,
    * it calculates only the partial sums which contain at most max_element_count elements in the addition.
    * 
    * @param vec The vector to be multiplied with the matrix.
    * @param max_element_count The maximum number of elements to consider in the multiplication. A value of 0 will calculate all partial sums.
    *
    * @return A vector containing the partial sums of the multiplication.
    *
    * @throws None.
    */
    static std::vector<double> precompute_partial_sums(std::vector<double> vec, 
                                                        size_t max_element_count = 0) {
                                                            
        size_t limit = max_element_count == 0 ? vec.size() : max_element_count;
        return _precompute_partial_sums(vec, limit, std::vector<double>{0.0}, 0);
    }
};