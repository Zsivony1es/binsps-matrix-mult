#include <vector>
#include <string>
#include <bitset>
#include <gtest/gtest.h>

#include "../src/utils/Utils.cpp"
#include "../src/PartialSum.cpp"

TEST(PartialSumTest, TestPartialSum) {
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    std::unordered_map<std::bitset<4>, double> expected = {
        {0b0000, 0.0}, {0b0001, 1.0}, {0b0010, 2.0}, {0b0100, 3.0}, {0b1000, 4.0}, 
        {0b0011, 3.0}, {0b0101, 4.0}, {0b0110, 5.0}, {0b1001, 5.0}, {0b1010, 6.0}, 
        {0b1100, 7.0}, {0b0111, 6.0}, {0b1011, 7.0}, {0b1101, 8.0}, {0b1110, 9.0}, {0b1111, 10.0}
    };

    auto result = PartialSum::precompute_partial_sums<4>(vec);

    ASSERT_EQ(result, expected);
}

TEST(PartialSumTest, TestPartialSumTerminatesWithLargerInput) {
    std::vector<double> vec;
    vec.resize(100, 1.0);

    uint runtime = Utils::time_exec(
        [&vec](){PartialSum::precompute_partial_sums<100>(vec, 15);}
    );

    ASSERT_LT(runtime, 30000);
}


TEST(PartialSumTest, TestPartialSumWithLimit) {
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    std::unordered_map<std::bitset<4>, double> expected = {
        {0b0000, 0.0}, {0b0001, 1.0}, {0b0010, 2.0}, {0b0100, 3.0}, {0b1000, 4.0}, 
        {0b0011, 3.0}, {0b0101, 4.0}, {0b0110, 5.0}, {0b1001, 5.0}, {0b1010, 6.0}, 
        {0b1100, 7.0}
    };

    auto result = PartialSum::precompute_partial_sums<4>(vec, 2);

    ASSERT_EQ(result, expected);
}

TEST(PartialSumTest, TestWorsePartialSum) {
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    std::unordered_map<std::bitset<4>, double> expected = {
        {0b0000, 0.0}, {0b0001, 1.0}, {0b0010, 2.0}, {0b0100, 3.0}, {0b1000, 4.0}, 
        {0b0011, 3.0}, {0b0101, 4.0}, {0b0110, 5.0}, {0b1001, 5.0}, {0b1010, 6.0}, 
        {0b1100, 7.0}, {0b0111, 6.0}, {0b1011, 7.0}, {0b1101, 8.0}, {0b1110, 9.0}, {0b1111, 10.0}
    };

    auto result = PartialSum::worse_precompute_partial_sums<4>(vec);

    ASSERT_EQ(result, expected);
}

TEST(PartialSumTest, TestWorsePartialSumWithLimit) {
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    std::unordered_map<std::bitset<4>, double> expected = {
        {0b0000, 0.0}, {0b0001, 1.0}, {0b0010, 2.0}, {0b0100, 3.0}, {0b1000, 4.0}, 
        {0b0011, 3.0}, {0b0101, 4.0}, {0b0110, 5.0}, {0b1001, 5.0}, {0b1010, 6.0}, 
        {0b1100, 7.0}
    };

    auto result = PartialSum::worse_precompute_partial_sums<4>(vec, 2);

    ASSERT_EQ(result, expected);
}