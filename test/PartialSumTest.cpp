#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "../src/PartialSum.cpp"

TEST(PartialSumTest, TestPartialSum) {
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> expected = {0.0, 4.0, 3.0, 7.0, 2.0, 6.0, 5.0, 9.0, 1.0, 5.0, 4.0, 8.0, 3.0, 7.0, 6.0, 10.0};

    std::vector<double> result = PartialSum::precompute_partial_sums(vec);

    ASSERT_EQ(result, expected);
}