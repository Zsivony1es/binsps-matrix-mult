#include <vector>
#include <string>
#include <bitset>
#include <gtest/gtest.h>
#include "../src/PartialSum.cpp"

TEST(PartialSumTest, TestPartialSum) {
    std::array<double, 4> array = {1.0, 2.0, 3.0, 4.0};
    std::unordered_map<std::bitset<4>, double> expected = {
        {0b0000, 0.0}, {0b0001, 1.0}, {0b0010, 2.0}, {0b0100, 3.0}, {0b1000, 4.0}, 
        {0b0011, 3.0}, {0b0101, 4.0}, {0b0110, 5.0}, {0b1001, 5.0}, {0b1010, 6.0}, 
        {0b1100, 7.0}, {0b0111, 6.0}, {0b1011, 7.0}, {0b1101, 8.0}, {0b1110, 9.0}, {0b1111, 10.0}
    };

    auto result = PartialSum::precompute_partial_sums(array);

    ASSERT_EQ(result, expected);
}

TEST(PartialSumTest, TestPartialSumWithLimit) {
    std::array<double, 4> array = {1.0, 2.0, 3.0, 4.0};
    std::unordered_map<std::bitset<4>, double> expected = {
        {0b0000, 0.0}, {0b0001, 1.0}, {0b0010, 2.0}, {0b0100, 3.0}, {0b1000, 4.0}, 
        {0b0011, 3.0}, {0b0101, 4.0}, {0b0110, 5.0}, {0b1001, 5.0}, {0b1010, 6.0}, 
        {0b1100, 7.0}
    };

    auto result = PartialSum::precompute_partial_sums(array, 2);

    ASSERT_EQ(result, expected);
}
