#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "../src/PartialSum.cpp"

TEST(PartialSumTest, TestPartialSum) {
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    std::unordered_map<size_t, double> expected = {
        {0, 0.0}, {1, 1.0}, {2, 2.0}, {4, 3.0}, {8, 4.0}, {3, 3.0}, {5, 4.0}, {9, 5.0}, 
        {6, 5.0}, {10, 6.0}, {12, 7.0}, {7, 6.0}, {11, 7.0}, {13, 8.0}, {14, 9.0}, {15, 10.0}
    };

    auto result = PartialSum::precompute_partial_sums(vec);

    ASSERT_EQ(result, expected);
}

TEST(PartialSumTest, TestPartialSumWithLimit) {
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    std::unordered_map<size_t, double> expected = {
        {0, 0.0}, {1, 1.0}, {2, 2.0}, {4, 3.0}, {8, 4.0}, 
        {3, 3.0}, {5, 4.0}, {9, 5.0}, {6, 5.0}, {10, 6.0}, {12, 7.0}
    };

    auto result = PartialSum::precompute_partial_sums(vec, 2);

    ASSERT_EQ(result, expected);
}