#pragma once
#pragma GCC diagnostic ignored "-Wshift-count-overflow"

#include <cmath>

class PartialSum {
private:
    template <size_t N>
    static void generate_combinations(int K, std::unordered_map<std::bitset<N>, double>& result, std::bitset<N>& current, int start, int ones_count) {
        if (ones_count > K) {
            return;
        }
        if (ones_count == K) {
            result.insert({current, 0.0});
            return;
        }

        for (int i = start; i < N; ++i) {
            current.set(i);
            generate_combinations(K, result, current, i + 1, ones_count + 1);
            current.reset(i);
        }

        // When fewer than K ones are needed, push the current combination
        if (ones_count < K) {
            result.insert({current, 0.0});
        }
    }

    template <size_t N>
    static std::unordered_map<std::bitset<N>, double> generate_binary_arrays(int K) {
        std::unordered_map<std::bitset<N>, double> result;
        std::bitset<N> current;
        PartialSum::generate_combinations<N>(K, result, current, 0, 0);
        return result;
    }

public:

    /**
    * Computes all combinations of sums of elements in the vector. If max_element_count is specified,
    * it calculates only the partial sums which contain at most max_element_count elements in the addition.
    * 
    * @param vec The vector containing the elements.
    * @param max_element_count The maximum number of elements that can be included in a partial sum. A value of 0 will calculate all partial sums.
    *
    * @return A map of a bitset, which represents which elements are part of the sum, and the sum of the elements.
    *
    * @throws None.
    */
    template <size_t N>
    static std::unordered_map<std::bitset<N>, double> precompute_partial_sums(std::vector<double> vec, 
                                                                              size_t max_element_count = 0) {
        if (max_element_count == 0) {
            max_element_count = N;
        }

        int total_comb = 1 << N;
        std::unordered_map<std::bitset<N>, double> result;

        for (int i = 0; i < total_comb; ++i) {
            auto key = std::bitset<N>(i);
            int bit_count = key.count();
            if (bit_count > max_element_count) {
                continue;
            }

            double sum = 0;            
            for (int j = 0; j < N; ++j) {
                if (i & (1 << j)) {
                    sum += vec[j];
                }
            }
            result[key] = sum;
        }

        return result;
    }

    /**
    * Computes all combinations of sums of elements in the vector. If max_element_count is specified,
    * it calculates only the partial sums which contain at most max_element_count elements in the addition.
    * 
    * @param vec The vector containing the elements.
    * @param max_element_count The maximum number of elements that can be included in a partial sum. A value of 0 will calculate all partial sums.
    *
    * @return A map of a bitset, which represents which elements are part of the sum, and the sum of the elements.
    *
    * @throws None.
    */
    template <size_t N>
    static std::unordered_map<std::bitset<N>, double> worse_precompute_partial_sums(std::vector<double> vec, 
                                                                                  size_t max_element_count = 0) {
        if (max_element_count == 0) {
            max_element_count = N;
        }

        std::unordered_map<std::bitset<N>, double> result = PartialSum::generate_binary_arrays<N>(max_element_count);

        for (auto& b : result) {
            for (int i = 0; i < N; ++i) {
                b.second += (b.first[i]) ? vec[i] : 0.0;
            }
        }

        return result;
    }
};