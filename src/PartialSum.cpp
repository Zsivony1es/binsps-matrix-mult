#pragma once

#include <cmath>

class PartialSum {
public:

    /**
    * Computes all combinations of sums of elements in the vector. If max_element_count is specified,
    * it calculates only the partial sums which contain at most max_element_count elements in the addition.
    * 
    * @param vec The vector to be multiplied with the matrix.
    * @param max_element_count The maximum number of elements that can be included in a partial sum. A value of 0 will calculate all partial sums.
    *
    * @return A vector containing the partial sums of the multiplication.
    *
    * @throws None.
    */
    static std::unordered_map<size_t, double> precompute_partial_sums(std::vector<double> vec, 
                                                        size_t max_element_count = 0) {
        if (max_element_count == 0) {
            max_element_count = vec.size();
        }                         

        int N = vec.size();
        int total_comb = 1 << N;
        std::unordered_map<size_t, double> result;

        for (int i = 0; i < total_comb; ++i) {
            int bit_count = std::bitset<32>(i).count();
            if (bit_count > max_element_count) {
                continue;
            }

            double sum = 0;            
            for (int j = 0; j < N; ++j) {
                if (i & (1 << j)) {
                    sum += vec[j];
                }
            }
            result[i] = sum;
        }

        return result;
    }
};